


#import <UIKit/UIKit.h>

@class SWRevealViewController;
@protocol SWRevealViewControllerDelegate;

#pragma mark - SWRevealViewController Class

// Enum values for setFrontViewPosition:animated:
typedef NS_ENUM( NSInteger, FrontViewPosition)
{
    // Front controller is removed from view. Animated transitioning from this state will cause the same
    // effect than animating from FrontViewPositionLeftSideMost. Use this instead of FrontViewPositionLeftSideMost when
    // you want to remove the front view controller view from the view hierarchy.
    FrontViewPositionLeftSideMostRemoved,
    
    // Left most position, front view is presented left-offseted by rightViewRevealWidth+rigthViewRevealOverdraw
    FrontViewPositionLeftSideMost,
    
    // Left position, front view is presented left-offseted by rightViewRevealWidth
    FrontViewPositionLeftSide,

    // Center position, rear view is hidden behind front controller
	FrontViewPositionLeft,
    
    // Right possition, front view is presented right-offseted by rearViewRevealWidth
	FrontViewPositionRight,
    
    // Right most possition, front view is presented right-offseted by rearViewRevealWidth+rearViewRevealOverdraw
	FrontViewPositionRightMost,
    
    // Front controller is removed from view. Animated transitioning from this state will cause the same
    // effect than animating from FrontViewPositionRightMost. Use this instead of FrontViewPositionRightMost when
    // you intent to remove the front controller view from the view hierarchy.
    FrontViewPositionRightMostRemoved,
    
};

// Enum values for toggleAnimationType
typedef NS_ENUM(NSInteger, SWRevealToggleAnimationType)
{
    SWRevealToggleAnimationTypeSpring,    // <- produces a spring based animation
    SWRevealToggleAnimationTypeEaseOut,   // <- produces an ease out curve animation
};


@interface SWRevealViewController : UIViewController

/* Basic API */

// Object instance init and rear view setting
- (id)initWithRearViewController:(UIViewController *)rearViewController frontViewController:(UIViewController *)frontViewController;

// Rear view controller, can be nil if not used
@property (nonatomic) UIViewController *rearViewController;
- (void)setRearViewController:(UIViewController *)rearViewController animated:(BOOL)animated;

// Optional right view controller, can be nil if not used
@property (nonatomic) UIViewController *rightViewController;
- (void)setRightViewController:(UIViewController *)rightViewController animated:(BOOL)animated;

// Front view controller, can be nil on initialization but must be supplied by the time the view is loaded
@property (nonatomic) UIViewController *frontViewController;
- (void)setFrontViewController:(UIViewController *)frontViewController animated:(BOOL)animated;

// Sets the frontViewController using a default set of chained animations consisting on moving the
// presented frontViewController to the right most possition, replacing it, and moving it back to the left position
- (void)pushFrontViewController:(UIViewController *)frontViewController animated:(BOOL)animated;

// Sets the frontViewController position. You can call the animated version several times with different
// positions to obtain a set of animations that will be performed in order one after the other.
@property (nonatomic) FrontViewPosition frontViewPosition;
- (void)setFrontViewPosition:(FrontViewPosition)frontViewPosition animated:(BOOL)animated;

// The following methods are meant to be directly connected to the action method of a button
// to perform user triggered postion change of the controller views. This is ussually added to a
// button on top left or right of the frontViewController
- (IBAction)revealToggle:(id)sender;
- (IBAction)rightRevealToggle:(id)sender; // <-- simetric implementation of the above for the rightViewController

// Toogles the current state of the front controller between Left or Right and fully visible
// Use setFrontViewPosition to set a particular position
- (void)revealToggleAnimated:(BOOL)animated;
- (void)rightRevealToggleAnimated:(BOOL)animated; // <-- simetric implementation of the above for the rightViewController

// The following method will provide a panGestureRecognizer suitable to be added to any view
// in order to perform usual drag and swipe gestures to reveal the rear views. This is usually added to the top bar
// of a front controller, but it can be added to your frontViewController view or to the reveal controller view to provide full screen panning.
// By default, the panGestureRecognizer is added to the view containing the front controller view. To keep this default behavior
// you still need to call this method, just don't add it to any of your views. The default setup allows you to dissable
// user interactions on your controller views without affecting the recognizer.
- (UIPanGestureRecognizer*)panGestureRecognizer;

// The following method will provide a tapGestureRecognizer suitable to be added to any view on the frontController
// for concealing the rear views. By default no tap recognizer is created or added to any view, however if you call this method after
// the controller's view has been loaded the recognizer is added to the reveal controller's front container view.
// Thus, you can disable user interactions on your frontViewController view without affecting the tap recognizer.
- (UITapGestureRecognizer*)tapGestureRecognizer;

/* The following properties are provided for further customization, they are set to default values on initialization,
   you do not generally have to set them */

// Defines how much of the rear or right view is shown, default is 260.
// Negative values indicate that the reveal width should be computed by substracting the full front view width,
// so the revealed frontView width is kept constant when bounds change as opposed to the rear or right width.
@property (nonatomic) CGFloat rearViewRevealWidth;
@property (nonatomic) CGFloat rightViewRevealWidth; // <-- simetric implementation of the above for the rightViewController

// Defines how much of an overdraw can occur when dragging further than 'rearViewRevealWidth', default is 60.
@property (nonatomic) CGFloat rearViewRevealOverdraw;
@property (nonatomic) CGFloat rightViewRevealOverdraw;   // <-- simetric implementation of the above for the rightViewController

// Defines how much displacement is applied to the rear view when animating or dragging the front view, default is 40.
@property (nonatomic) CGFloat rearViewRevealDisplacement;
@property (nonatomic) CGFloat rightViewRevealDisplacement;  // <-- simetric implementation of the above for the rightViewController

// Defines a width on the border of the view attached to the panGesturRecognizer where the gesture is allowed,
// default is 0 which means no restriction.
@property (nonatomic) CGFloat draggableBorderWidth;

// If YES (the default) the controller will bounce to the Left position when dragging further than 'rearViewRevealWidth'
@property (nonatomic) BOOL bounceBackOnOverdraw;
@property (nonatomic) BOOL bounceBackOnLeftOverdraw;  // <-- simetric implementation of the above for the rightViewController

// If YES (default is NO) the controller will allow permanent dragging up to the rightMostPosition
@property (nonatomic) BOOL stableDragOnOverdraw;
@property (nonatomic) BOOL stableDragOnLeftOverdraw; // <-- simetric implementation of the above for the rightViewController

// If YES (default is NO) the front view controller will be ofsseted vertically by the height of a navigation bar.
// Use this on iOS7 when you add an instance of RevealViewController as a child of a UINavigationController (or another SWRevealViewController)
// and you want the front view controller to be presented below the navigation bar of its UINavigationController grand parent.
// The rearViewController will still appear full size and blurred behind the navigation bar of its UINavigationController grand parent
@property (nonatomic) BOOL presentFrontViewHierarchically;

// Velocity required for the controller to toggle its state based on a swipe movement, default is 250
@property (nonatomic) CGFloat quickFlickVelocity;

// Duration for the revealToggle animation, default is 0.25
@property (nonatomic) NSTimeInterval toggleAnimationDuration;

// Animation type, default is SWRevealToggleAnimationTypeSpring
@property (nonatomic) SWRevealToggleAnimationType toggleAnimationType;

// When animation type is SWRevealToggleAnimationTypeSpring determines the damping ratio, default is 1
@property (nonatomic) CGFloat springDampingRatio;

// Duration for animated replacement of view controllers
@property (nonatomic) NSTimeInterval replaceViewAnimationDuration;

// Defines the radius of the front view's shadow, default is 2.5f
@property (nonatomic) CGFloat frontViewShadowRadius;

// Defines the radius of the front view's shadow offset default is {0.0f,2.5f}
@property (nonatomic) CGSize frontViewShadowOffset;

// Defines the front view's shadow opacity, default is 1.0f
@property (nonatomic) CGFloat frontViewShadowOpacity;

// Defines the front view's shadow color, default is blackColor
@property (nonatomic) UIColor *frontViewShadowColor;

// Defines whether the controller should clip subviews to its view bounds. Default is NO.
// Set this to YES when you are presenting this controller as a non full-screen child of a
// custom container controller which does not explicitly clips its subviews.
@property (nonatomic) BOOL clipsViewsToBounds;

// Defines whether your views clicable area extends beyond the bounds of this controller. Default is NO.
// Set this to YES if you are presenting this controller as a non full-screen child of a custom container and you are not
// clipping your front view to this controller bounds.
@property (nonatomic) BOOL extendsPointInsideHit;

/* The class properly handles all the relevant calls to appearance methods on the contained controllers.
   Moreover you can assign a delegate to let the class inform you on positions and animation activity */

// Delegate
@property (nonatomic,weak) id<SWRevealViewControllerDelegate> delegate;

@end


#pragma mark - SWRevealViewControllerDelegate Protocol

typedef enum
{
    SWRevealControllerOperationNone,
    SWRevealControllerOperationReplaceRearController,
    SWRevealControllerOperationReplaceFrontController,
    SWRevealControllerOperationReplaceRightController,
    
} SWRevealControllerOperation;


@protocol SWRevealViewControllerDelegate<NSObject>

@optional

// The following delegate methods will be called before and after the front view moves to a position
- (void)revealController:(SWRevealViewController *)revealController willMoveToPosition:(FrontViewPosition)position;
- (void)revealController:(SWRevealViewController *)revealController didMoveToPosition:(FrontViewPosition)position;

// This will be called inside the reveal animation, thus you can use it to place your own code that will be animated in sync
- (void)revealController:(SWRevealViewController *)revealController animateToPosition:(FrontViewPosition)position;

// Implement this to return NO when you want the pan gesture recognizer to be ignored
- (BOOL)revealControllerPanGestureShouldBegin:(SWRevealViewController *)revealController;

// Implement this to return NO when you want the tap gesture recognizer to be ignored
- (BOOL)revealControllerTapGestureShouldBegin:(SWRevealViewController *)revealController;

// Implement this to return YES if you want other gesture recognizer to share touch events with the pan gesture
- (BOOL)revealController:(SWRevealViewController *)revealController
    panGestureRecognizerShouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer;

// Implement this to return YES if you want other gesture recognizer to share touch events with the tap gesture
- (BOOL)revealController:(SWRevealViewController *)revealController
    tapGestureRecognizerShouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer;

// Called when the gestureRecognizer began and ended
- (void)revealControllerPanGestureBegan:(SWRevealViewController *)revealController;
- (void)revealControllerPanGestureEnded:(SWRevealViewController *)revealController;

// The following methods provide a means to track the evolution of the gesture recognizer.
// The 'location' parameter is the X origin coordinate of the front view as the user drags it
// The 'progress' parameter is a number ranging from 0 to 1 indicating the front view location relative to the
//   rearRevealWidth or rightRevealWidth. 1 is fully revealed, dragging ocurring in the overDraw region will result in values above 1.
// The 'overProgress' parameter is a number ranging from 0 to 1 indicating the front view location relative to the
//   overdraw region. 0 is fully revealed, 1 is fully overdrawn. Negative values occur inside the normal reveal region
- (void)revealController:(SWRevealViewController *)revealController panGestureBeganFromLocation:(CGFloat)location progress:(CGFloat)progress overProgress:(CGFloat)overProgress;
- (void)revealController:(SWRevealViewController *)revealController panGestureMovedToLocation:(CGFloat)location progress:(CGFloat)progress overProgress:(CGFloat)overProgress;
- (void)revealController:(SWRevealViewController *)revealController panGestureEndedToLocation:(CGFloat)location progress:(CGFloat)progress overProgress:(CGFloat)overProgress;

// Notification of child controller replacement
- (void)revealController:(SWRevealViewController *)revealController willAddViewController:(UIViewController *)viewController
    forOperation:(SWRevealControllerOperation)operation animated:(BOOL)animated;
- (void)revealController:(SWRevealViewController *)revealController didAddViewController:(UIViewController *)viewController
    forOperation:(SWRevealControllerOperation)operation animated:(BOOL)animated;

// Support for custom transition animations while replacing child controllers. If implemented, it will be fired in response
// to calls to 'setXXViewController' methods
- (id<UIViewControllerAnimatedTransitioning>)revealController:(SWRevealViewController *)revealController
    animationControllerForOperation:(SWRevealControllerOperation)operation fromViewController:(UIViewController *)fromVC toViewController:(UIViewController *)toVC;

// DEPRECATED - The following delegate methods will be removed some time in the future
- (void)revealController:(SWRevealViewController *)revealController panGestureBeganFromLocation:(CGFloat)location progress:(CGFloat)progress; // (DEPRECATED)
- (void)revealController:(SWRevealViewController *)revealController panGestureMovedToLocation:(CGFloat)location progress:(CGFloat)progress; // (DEPRECATED)
- (void)revealController:(SWRevealViewController *)revealController panGestureEndedToLocation:(CGFloat)location progress:(CGFloat)progress; // (DEPRECATED)
@end


#pragma mark - UIViewController(SWRevealViewController) Category

// A category of UIViewController to let childViewControllers easily access their parent SWRevealViewController
@interface UIViewController(SWRevealViewController)

- (SWRevealViewController*)revealViewController;

@end


#pragma mark - StoryBoard support Classes

/* StoryBoard support */

// String identifiers to be applied to segues on a storyboard
extern NSString* const SWSegueRearIdentifier;  // this is @"sw_rear"
extern NSString* const SWSegueFrontIdentifier; // this is @"sw_front"
extern NSString* const SWSegueRightIdentifier; // this is @"sw_right"

/* This will allow the class to be defined on a storyboard */

// Use this along with one of the above segue identifiers to segue to the initial state
@interface SWRevealViewControllerSegueSetController : UIStoryboardSegue
@end

// Use this to push a view controller
@interface SWRevealViewControllerSeguePushController : UIStoryboardSegue
@end


//#pragma mark - SWRevealViewControllerSegue (DEPRECATED)
//
//@interface SWRevealViewControllerSegue : UIStoryboardSegue     // DEPRECATED: USE SWRevealViewControllerSegueSetController instead
//@property (nonatomic, strong) void(^performBlock)( SWRevealViewControllerSegue* segue, UIViewController* svc, UIViewController* dvc );
//@end
