/*
 * Copyright (c) 2007-2013 Migratory Data Systems (http://migratorydata.com)
 * ALL RIGHTS RESERVED. Use is subject to license terms.
 */
 
/** \file MigratoryDataListener.h
 * 
 * \brief Include the declaration of the \link MigratoryDataListener \endlink class.
 */

#import "MigratoryDataMessage.h"

/**
 * \brief Implementations of this interface can handle the real-time messages received for the subscribed subjects as well as various status notifications.
 *
 * Use the API method \link MigratoryDataClient::setListener: \endlink to register your listener implementation.
 */
@protocol MigratoryDataListener

/**
 * \brief This method handles the real-time messages received from a MigratoryData server for the subscribed subjects.
 *
 * \param message An object of type \link MigratoryDataMessage \endlink .
 */
- (void)onMessage:(MigratoryDataMessage *)message;

/**
 * \brief This method handles the status notifications.
 *
 * The possible values of the <code>status</code> parameter are:</p>
 *
 * \li <tt>\link NOTIFY_SERVER_UP \endlink</tt> indicates that the client successfully connected to the
 *      MigratoryData server provided in the detail information of the status notification
 *
 * \li <tt>\link NOTIFY_SERVER_DOWN \endlink</tt> indicates that the client was not able to connect to the
 *      MigratoryData server provided in the detail information of the status notification
 *
 * \li <tt>\link NOTIFY_DATA_SYNC \endlink</tt> indicates that, after a failover reconnection, the client
 *      successfully synchronized the subject given in the detail information of the status notification. Moreover, the client
 *      received the messages published during the failover period for this subject.
 *
 * \li <tt>\link NOTIFY_DATA_RESYNC \endlink</tt> indicates that, after a failover reconnection, the client
 *      successfully synchronized the subject given in the detail information of the status notification. However, the client
 *      have not received the potential messages published during the failover period for this subject, the client
 *      behaving like a new client which just connected to the MigratoryData server.
 *
 * \li <tt>\link NOTIFY_SUBSCRIBE_ALLOW \endlink</tt> indicates that the client -- identified with the token given
 *     in the argument of <tt>\link MigratoryDataClient::setEntitlementToken: \endlink</tt> -- is allowed to subscribe to the subject provided
 *     in the detail information of the status notification
 *
 * \li <tt>\link NOTIFY_SUBSCRIBE_DENY \endlink</tt> indicates that the client -- identified with the token given
 *     in the argument of <tt>\link MigratoryDataClient::setEntitlementToken: \endlink</tt> -- is not allowed to subscribe to the subject provided
 *     in the detail information of the status notification
 *
 * \li <tt>\link NOTIFY_PUBLISH_OK \endlink</tt> indicates that the client successfully published the message having
 * 	   the closure data provided in the detail information of the status notification
 *
 * \li <tt>\link NOTIFY_PUBLISH_FAILED \endlink</tt> indicates that the client was unable to publish the message having
 * 	   the closure data provided in the detail information of the status notification
 *
 * \li <tt>\link NOTIFY_PUBLISH_DENIED \endlink</tt> indicates that the client was unable to publish the message having
 * 	   the closure data provided in the detail information of the status notification because the client -- identified with the token given
 * 	   in the argument of <tt>\link MigratoryDataClient::setEntitlementToken: \endlink</tt> -- is not allowed to publish on the subject of the message
 *
 * \li <tt>\link NOTIFY_PUBLISH_NO_SUBSCRIBER \endlink</tt> indicates that the client was unable to publish the message having
 *	   the closure data provided in the detail information of the status notification because there is no client subscribed to the subject of the message
 *
 * \param status The type of the status notification (see the possible values above).
 *
 * \param info The detail information of the status notification.
 */
- (void)onStatus:(NSString *)status info:(NSString *)info;

@end
