//
//  ViewController.h
//  LF
//
//  Created by Joe Physwf on 7/16/14.
//  Copyright (c) 2014 Joe Physwf. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <UIKit/UIKit.h>
#import <MAMapKit/MAMapKit.h>

@interface ViewController : UIViewController<MAMapViewDelegate>
{
}
@property (nonatomic, strong) MAMapView *mapView;
@end
/*
@interface BaseMapViewController:UIViewController<MAMapViewDelegate>
@property (nonatomic, strong) MAMapView *mapView;
@end
*/