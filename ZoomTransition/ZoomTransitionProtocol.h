//
//  ZoomTransitionProtocol.h
//  ZoomSegueExample
//
// Created by Denys Telezhkin on 30.06.14.
//
//  Copyright (c) 2014 Denys Telezhkin
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef void(^ZoomAnimationBlock)(UIImageView * animatedSnapshot, UIView * sourceView, UIView * destinationView);
typedef void(^ZoomCompletionBlock)(UIImageView * animatedSnapshot, UIView * sourceView, UIView * destinationView, void(^completion)(void));

/**
 ZoomTransitionProtocol should be implemented by UIViewControllers, that wish to participate in zoom transition.
 */

@protocol ZoomTransitionProtocol <NSObject>

/**
 UIView, that will be used for zoom transition. Both source and destination view controllers need to implement this method, otherwise ZoomInteractiveTransition will not be performed.
 
 @param isSource Boolean, that is true if the view controller implementing this method is the source view controller of a transition.
 
 @return UIView, that will participate in transition.
 */
-(UIView *)viewForZoomTransition:(BOOL)isSource;

@optional

/**
 By default, ZoomInteractiveTransition will choose bigger snapshot from source and destination view snapshots. Initial chosen snapshot will be passed to this method. You may choose to change it, or provide completely different snapshot that suits your needs better. Keep in mind, snapshot will be resized to destination view frame.
 
 @param snapshot Snapshot, that was prepared by ZoomInteractiveTransition 
 
 @return snapshot, that you wish to use for zoom animation.
 */
-(UIImageView *)initialZoomViewSnapshotFromProposedSnapshot:(UIImageView *)snapshot;


/**
 Custom animation block, that will be called inside UIView animateKeyFramesWithDuration:delay:options:animations:completion: method alongside with zooming animation. You can add your own keyframes to animation if you need.
 
 @return Animation block.
 */
-(ZoomAnimationBlock)animationBlockForZoomTransition;


/**
 Custom animation block, that will be called inside UIView animateKeyFramesWithDuration:delay:options:animations:completion: method when the animation is completed.
 
 @return Animation block.
 */
-(ZoomCompletionBlock)completionBlockForZoomTransition;


/**
 Decide if ZoomInteractiveTransition animator object is allowed.
 
 @param operation The type of transition operation that is occurring. For a list of possible values, see the “UINavigationControllerOperation” constants.
 
 @param fromVC The currently visible view controller.
 
 @param toVC The view controller that should be visible at the end of the transition.
 
 @return Yes to allow the zoom transition.
 */
-(BOOL)shouldAllowZoomTransitionForOperation:(UINavigationControllerOperation)operation
                          fromViewController:(UIViewController *)fromVC
                            toViewController:(UIViewController *)toVC;

/**
 If ZoomInteractiveTransition animator object isn't allowed, return another one instead.
 
 @param toVC The view controller that should be visible at the end of the transition.
 
 @return The animator object responsible for managing the transition animations, or nil if you want to use the standard navigation controller transitions. The object you return must conform to the UIViewControllerAnimatorTransitioning protocol.
 */
-(id<UIViewControllerAnimatedTransitioning>)animationControllerForTransitionToViewController:(UIViewController *)toVC;

@end
