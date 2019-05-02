/*
 * Copyright (c) 2007-2014 Migratory Data Systems (http://migratorydata.com)
 * ALL RIGHTS RESERVED. Use is subject to license terms.
 */
#import <Foundation/Foundation.h>
#import "MigratoryDataField.h"

/** \file MigratoryDataMessage.h
 * 
 * \brief Include the declaration of the \link MigratoryDataMessage \endlink class.
 */
 
/**
 * \brief Represent a message
 */
@interface MigratoryDataMessage : NSObject {
@private
	NSString *_subject;
	NSString *_content;
    NSString *_closure;
	NSArray *_fields;
    bool _isSnapshot;
}

/**
 * \brief Create a MigratoryDataMessage object
 *
 * \param subject The subject of the message
 * \param content The content of the message
 */
- (id) init: (NSString *)subject content:(NSString *)content;

/**
 * \brief Create a MigratoryDataMessage object
 *
 * \param subject The subject of the message
 * \param content The content of the message
 * \param fields  The fields of the message
 */
- (id) init: (NSString *)subject content:(NSString *)content fields:(NSArray *)fields;

/**
 * \brief Create a MigratoryDataMessage object
 *
 * \param subject The subject of the message
 * \param content The content of the message
 * \param closure The closure of the message
 */
- (id) init: (NSString *)subject content:(NSString *)content closure:(NSString *)closure;

/**
 * \brief Create a MigratoryDataMessage object
 *
 * \param subject The subject of the message
 * \param content The content of the message
 * \param fields  The fields of the message
 * \param closure The closure of the message
 */
- (id) init: (NSString *)subject content:(NSString *)content fields:(NSArray *)fields closure:(NSString *)closure;

/// @cond
- (id) init: (NSString *)subject content:(NSString *)content fields:(NSArray *)fields closure:(NSString *)closure snapshot:(bool)isSnapshot;
/// @endcond

/**
 * \brief Get the subject of the message
 *
 * \return A string representing the subject of the message
 */
- (NSString *) getSubject;

/**
 * \brief Get the content of the message
 *
 * \return A string representing the content of the message
 */
- (NSString *) getContent;

/**
 * \brief Get the fields of the message
 *
 * \return The fields of the message as a list of \link MigratoryDataField \endlink objects
 */
- (NSArray *) getFields;

/**
 * \brief Get the closure of the message
 *
 * \return The closure data of the message
 */
- (NSString *) getClosure;

/**
 * \brief Test whether the message is a snapshot message or not
 *
 * \return true if the message is a snapshot message
 */
- (bool) isSnapshot;

@end
