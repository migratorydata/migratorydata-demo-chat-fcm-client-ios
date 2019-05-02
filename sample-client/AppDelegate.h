#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "MigratoryDataClient.h"
#import "SampleListener.h"

@interface AppDelegate : NSObject <UIApplicationDelegate> {
    
    UIWindow *window;
    
    UITextField *liveStatus;
    UITextField *liveMessage;
    
    MigratoryDataClient *client;
    SampleListener *listener;
    
    NSMutableArray *subjectList;
    NSMutableArray *serverList;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet UITextField *liveStatus;
@property (nonatomic, retain) IBOutlet UITextField *liveMessage;

@end
