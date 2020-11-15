///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_POLLSTRATEGYBASE_H
#define SYSTEM_KAFKA_POLLSTRATEGYBASE_H
#include "System/Kafka/Queue.h"
#include "System/Kafka/TopicPartitionList.h"
#include "System/Kafka/PollInterface.h"
#include "System/Kafka/Macros.h"
#include "System/nonstd/any.hpp"
#include <map>
namespace System
{
	namespace Kafka
	{
		/**
		* \brief Contains a partition queue and generic metadata which can be used to store
		*        related (user-specific) information.
		*/
		struct QueueData {
			Queue       queue;
			nonstd::any  metadata;
		};

		/**
		* \class PollStrategyBase
		*
		* \brief Base implementation of  the PollInterface
		*/
		class SYSTEM_API PollStrategyBase : public PollInterface {
		public:
			using QueueMap = std::map<TopicPartition, QueueData>;

			/**
			* \brief Constructor
			*
			* \param consumer A reference to the polled consumer instance
			*/
			explicit PollStrategyBase(Consumer& consumer);

			/**
			* \brief Destructor
			*/
			~PollStrategyBase();

			/**
			* \sa PollInterface::set_timeout
			*/
			void set_timeout(std::chrono::milliseconds timeout) override;

			/**
			* \sa PollInterface::get_timeout
			*/
			std::chrono::milliseconds get_timeout() override;

			/**
			* \sa PollInterface::get_consumer
			*/
			Consumer& get_consumer() final;

			/**
			* \brief Creates partitions queues associated with the supplied partitions.
			*
			* This method contains a default implementation. It adds all the new queues belonging
			* to the provided partition list and calls reset_state().
			* To be used with static consumers.
			*
			* \param partitions Assigned topic partitions.
			*/
			virtual void assign(TopicPartitionList& partitions);

			/**
			* \brief Removes partitions queues associated with the supplied partitions.
			*
			* This method contains a default implementation. It removes all the queues
			* belonging to the provided partition list and calls reset_state().
			* To be used with static consumers.
			*
			* \param partitions Revoked topic partitions.
			*/
			virtual void revoke(const TopicPartitionList& partitions);

			/**
			* \brief Removes all partitions queues associated with the supplied partitions.
			*
			* This method contains a default implementation. It removes all the queues
			* currently assigned and calls reset_state(). To be used with static consumers.
			*/
			virtual void revoke();

		protected:
			/**
			* \brief Get the queues from all assigned partitions
			*
			* \return A map of queues indexed by partition
			*/
			QueueMap& get_partition_queues();

			/**
			* \brief Get the main consumer queue which services the underlying Consumer object
			*
			* \return The consumer queue
			*/
			QueueData& get_consumer_queue();

			/**
			* \brief Reset the internal state of the queues.
			*
			* Use this function to reset the state of any polling strategy or algorithm.
			*
			* \remark This function gets called by on_assignement(), on_revocation() and on_rebalance_error()
			*/
			virtual void reset_state();

			/**
			* \brief Function to be called when a new partition assignment takes place
			*
			* This method contains a default implementation. It calls assign()
			* and invokes the user assignment callback.
			*
			* \param partitions Assigned topic partitions
			*/
			virtual void on_assignment(TopicPartitionList& partitions);

			/**
			* \brief Function to be called when an old partition assignment gets revoked
			*
			* This method contains a default implementation. It calls revoke()
			* and invokes the user revocation callback.
			*
			* \param partitions Revoked topic partitions
			*/
			virtual void on_revocation(const TopicPartitionList& partitions);

			/**
			* \brief Function to be called when a topic rebalance error happens
			*
			* This method contains a default implementation. Calls reset_state().
			*
			* \param error The rebalance error
			*/
			virtual void on_rebalance_error(Error error);

		private:
			Consumer&                           consumer_;
			QueueData                           consumer_queue_;
			QueueMap                            partition_queues_;
			Consumer::AssignmentCallback        assignment_callback_;
			Consumer::RevocationCallback        revocation_callback_;
			Consumer::RebalanceErrorCallback    rebalance_error_callback_;
		};
	}
}
#endif // !SYSTEM_KAFKA_POLLSTRATEGYBASE_H
