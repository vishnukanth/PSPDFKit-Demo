//
//  PSPDFEmbeddedTestController.h
//  EmbeddedExample
//
//  Copyright 2011 Peter Steinberger. All rights reserved.
//

/// Exmaple how to correctly embedd (in an iOS4 compatible way) the view controller within another view controller.
@interface PSPDFEmbeddedTestController : UIViewController

- (IBAction)appendDocument;
- (IBAction)replaceDocument;
- (IBAction)clearCache;

@property(nonatomic, retain) PSPDFViewController *pdfController;

@end
