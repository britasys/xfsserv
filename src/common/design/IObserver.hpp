#pragma once

#ifndef __H_IOBSERVER__
#define __H_IOBSERVER__

#include <mutex>
#include <functional>
#include <unordered_map>
#include <memory>

namespace __N_OBSERVER__
{
    using INDEX = unsigned short int;

    template <typename CONTEXT>
    using LAMBDA = std::function<void(const CONTEXT&)>;

    template <typename CONTEXT>
    class ISubscriber
    {
    private:
    protected:
    public:
        virtual void update(const CONTEXT&) = 0;
    };

    template <typename CONTEXT>
    class IPublisher
    {
    private:
		INDEX index{ 0 };
        std::mutex mx{};
        std::unordered_map<INDEX, std::shared_ptr<ISubscriber<CONTEXT>>> subscribers{};
        std::unordered_map<INDEX, LAMBDA<CONTEXT>> lambdas{};

    protected:
    public:
        INDEX subscribe(std::shared_ptr<ISubscriber<CONTEXT>> subscriber) noexcept
        {
		    std::lock_guard<std::mutex>lock(this->mx);

		    INDEX l_index = this->index;
		    auto l_mapRet = this->subscribers.insert(std::make_pair(l_index, subscriber));
		    if (false == l_mapRet.second)
		    	return -1;

		    this->index++;

		    return l_index;
        }
        
        INDEX subscribe(ISubscriber<CONTEXT>* pSubscriber) noexcept
        {
            return this->subscribe(std::make_shared<ISubscriber<CONTEXT>>(pSubscriber));
        }

        INDEX subscribe(LAMBDA<CONTEXT> lambda)
        {
		    std::lock_guard<std::mutex>lock(this->mx);

		    INDEX l_index = this->index;
		    auto l_mapRet = this->lambdas.insert(std::make_pair(l_index, lambda));
		    if (false == l_mapRet.second)
		    	return -1;

		    this->index++;

		    return l_index;
        }

        void Unsubscribe(const INDEX index) noexcept
        {
		    std::lock_guard<std::mutex>_lock(this->mx);

		    try {
		    	auto it = this->subscribers.find(index);
		    	if (it != this->subscribers.end())
		    		this->subscribers.erase(it);
		    } catch (...) { return; }
        }

        void notify_subscribers(const CONTEXT& context) noexcept
        {
		    std::lock_guard<std::mutex>_lock(this->mx);

		    for (const auto& subscriber : this->subscribers)
                if (subscriber.second)
		    	    subscriber.second->update(context);
        }

        void notify_lambdas(const CONTEXT& context) noexcept
        {
		    std::lock_guard<std::mutex>_lock(this->mx);

		    for (const auto& lambda : this->lambdas)
                if (lambda.second)
		    	    lambda.second(context);
        }
    };
} // !__N_OBSERVER__

#endif // !__H_IOBSERVER__