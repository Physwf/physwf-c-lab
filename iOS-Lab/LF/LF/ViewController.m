//
//  ViewController.m
//  LF
//
//  Created by Joe Physwf on 7/16/14.
//  Copyright (c) 2014 Joe Physwf. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    [MAMapServices sharedServices].apiKey = @"d4a92417dd29a8e5f2665da07402aef6";
    //AMapSearchAPI *search = [[AMapSearchAPI alloc] initWithSearchKey: @"您的key" Delegate:self];    //_mapView = 	[[MAMapView alloc] initWithFrame:(CGRectMake(0, 0, 640, 960))];
    //self.view = _mapView;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) viewWillAppear:(BOOL)animated
{
    //[super viewWillAppear: animated];
   // self.mapView=[[MAMapView alloc] initWithFrame:CGRectMake(0, 0, 320, 460)];
    //self.mapView.delegate = self;
    //[self.mapView addSubview:self.mapView];
}

@end

