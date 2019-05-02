#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "MigratoryDataListener.h"

@interface SampleListener : NSObject <MigratoryDataListener> {
	UITextField *messageTextField;
	UITextField *statusTextField;
    
    // UILocalNotification *notification;
}

- (id) initWithMessageField: (UITextField *)liveMessage statusField: (UITextField *)liveStatus;

@end
