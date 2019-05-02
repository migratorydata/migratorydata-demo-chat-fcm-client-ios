/*
 * Copyright (c) 2007-2014 Migratory Data Systems (http://migratorydata.com)
 * ALL RIGHTS RESERVED. Use is subject to license terms.
 */
#import <Foundation/Foundation.h>

/** \file MigratoryDataField.h
 * 
 * \brief Include the declaration of the \link MigratoryDataField \endlink class.
 */
 
/**
 * \brief Represent a message field.
 */
@interface MigratoryDataField : NSObject {
@private
	NSString *_name;
	NSString *_value;
}

/**
 * \brief Create a MigratoryDataField object.
 *
 * \param name The field name
 * \param value The field value
 */
- (id) init: (NSString *)name value:(NSString *)value;

/**
 * \brief Get the field name.
 *
 * \return A string representing the field name.
 */
- (NSString *) getName;

/**
 * \brief Get the field value.
 *
 * \return A string representing the field value.
 */
- (NSString *) getValue;

@end
