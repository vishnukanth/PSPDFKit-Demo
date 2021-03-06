//
//  PSPDFViewController.h
//  PSPDFKit
//
//  Copyright 2011 Peter Steinberger. All rights reserved.
//

#import "AQGridView.h"
#import <MessageUI/MessageUI.h>

@protocol PSPDFViewControllerDelegate;
@class PSPDFDocument, PSPDFScrollView, PSPDFScrobbleBar;

/// current active view mode.
enum {
    PSPDFViewModeDocument,
    PSPDFViewModeThumbnails
}typedef PSPDFViewMode;

/// active page mode.
enum {
    PSPDFPageModeSingle,   // Default on iPhone.
    PSPDFPageModeDouble,
    PSPDFPageModeAutomatic // single in portrait, double in landscape if the document's height > width. Default on iPad.
}typedef PSPDFPageMode;

/// active scrolling direction.
enum {
    PSPDFScrollingHorizontal, // default
    PSPDFScrollingVertical
}typedef PSPDFScrolling;

/// status bar style. (old status will be restored regardless of the style chosen)
enum {
    PSPDFStatusBarInherit,      /// don't change status bar style, but show/hide statusbar on HUD events
    PSPDFStatusBarSmartBlack,   /// use UIStatusBarStyleBlackOpaque on iPad, UIStatusBarStyleBlackTranslucent on iPhone.
    PSPDFStatusBarBlackOpaque,  /// Opaque Black everywhere
    PSPDFStatusBarDefaultWhite, /// Switch to default (white) statusbar
    PSPDFStatusBarDisable       /// never show status bar
}typedef PSPDFStatusBarStyleSetting;

/// The main view controller to display pdfs. Can be displayed in fullscreen or embedded.
/// When embedded, be sure to correctly relay the viewController calls of viewWillAppear/etc. (or use iOS5 view controller containment)
@interface PSPDFViewController : UIViewController <UIScrollViewDelegate, UIPopoverControllerDelegate, MFMailComposeViewControllerDelegate, AQGridViewDelegate, AQGridViewDataSource>

/// initialize with a document.
- (id)initWithDocument:(PSPDFDocument *)document;

/// control currently displayed page.
- (void)scrollToPage:(NSUInteger)page animated:(BOOL)animated;

/// control currently displayed page, optionally show/hide the HUD.
- (void)scrollToPage:(NSUInteger)page animated:(BOOL)animated hideHUD:(BOOL)hideHUD;

/// scroll to next page.
- (BOOL)scrollToNextPageAnimated:(BOOL)animated;

// scroll to previous page.
- (BOOL)scrollToPreviousPageAnimated:(BOOL)animated;

/// depending on pageMode, this returns true if two pages are displayed.
- (BOOL)isDualPageMode;

/// show a modal view controller with automatically added close button on the left side.
- (void)presentModalViewControllerWithCloseButton:(UIViewController *)controller;

/// reload scrollview. Call if you manually change the view width/height or some property inside PSPDFDocument. Usually not needed.
- (void)reloadData;

/// reload scrollview, scroll to specified page.
- (void)reloadDataAndScrollToPage:(NSUInteger)page;

/// checks if the current page is on the right side, when in double page mode. Page starts at 0.
- (BOOL)isRightPageInDoublePageNode:(NSUInteger)page;

/// register delegate to capture events, change properties.
@property(nonatomic, assign) id<PSPDFViewControllerDelegate> delegate;

/// document that will be displayed.
@property(nonatomic, retain) PSPDFDocument *document;

/// current page displayed, not landscape corrected. To change page, use scrollToPage.
@property(nonatomic, assign, readonly) NSUInteger page;

/// current page displayed, landscape corrected. To change page, use scrollToPage.
@property(nonatomic, assign, readonly) NSUInteger realPage;

/// view mode: PSPDFViewModeMagazine or PSPDFViewModeThumbnails.
@property(nonatomic, assign) PSPDFViewMode viewMode;

/// page mode: PSPDFPageModeSingle or PSPDFPageModeDouble.
@property(nonatomic, assign) PSPDFPageMode pageMode;

/// change scrolling direction. defaults to horizontal scrolling. (PSPDFScrollingHorizontal)
@property(nonatomic, assign) PSPDFScrolling pageScrolling;

/// shows first document page alone. Not relevant in PSPDFPageModeSinge. Defaults to NO.
@property(nonatomic, assign, getter=isDoublePageModeOnFirstPage) BOOL doublePageModeOnFirstPage;

/// allow zooming of small documents to screen width/height. Defaults to YES.
@property(nonatomic, assign, getter=isZoomingSmallDocumentsEnabled) BOOL zoomingSmallDocumentsEnabled;

/// if true, pages are fit to screen width, not to either height or width (which one is larger - usually height.) Defaults to NO.
/// iPhone switches to yes in willRotateToInterfaceOrientation - reset back to no if you don't want this.
/// fitWidth is currently not supported for vertical scrolling. This is a know limitation.
@property(nonatomic, assign, getter=isFittingWidth) BOOL fitWidth;

/// maximum zoom scale for the scrollview. Defaults to 5.0. Set before creating the view.
@property(nonatomic, assign) float maximumZoomScale;

/// page padding width between single/double pages. Defaults to 20.
@property(nonatomic, assign) CGFloat pagePadding;

/// pages that are kept in pageScrollView after last visible page. Defaults to 0. Don't set too high, needs lots of memory!
@property(nonatomic, assign) NSUInteger preloadedPagesPerSide;

/// enable/disable page shadow.
@property(nonatomic, assign, getter=isShadowEnabled) BOOL shadowEnabled;

/// saves the popoverController if currently displayed.
@property(nonatomic, retain) UIPopoverController *popoverController;

/// paging scroll view. (hosts scollviews for pdf)
@property(nonatomic, retain, readonly) UIScrollView *pagingScrollView;

/// if not set, we'll use scrollViewTexturedBackgroundColor as default.
@property(nonatomic, retain) UIColor *backgroundColor;

/// enables bottom scrobble bar [if HUD is displayed]. will be hidden automatically when in thumbnail mode. Defaults to YES. Set before loading view.
/// there's some more logic involved, e.g. is the default white statusbar not hidden on a HUD change.
@property(nonatomic, assign, getter=isSrobbleBarEnabled) BOOL scrobbleBarEnabled;

/// enables default header toolbar. Only displayed if inside UINavigationController. Defaults to YES. Set before loading view.
@property(nonatomic, assign, getter=isToolbarEnabled) BOOL toolbarEnabled;

/// enable/disable scrolling. can be used in special cases where scrolling is turned of (temporarily). Defaults to YES.
@property(nonatomic, assign, getter=isScrollingEnabled) BOOL scrollingEnabled;

/// status bar styling. Defaults to PSPDFStatusBarSmartBlack.
@property(nonatomic, assign) PSPDFStatusBarStyleSetting statusBarStyleSetting;

/// tap on begin/end of page scrolls to previous/next page. Defaults to YES.
@property(nonatomic, assign, getter=isScrollOnTapPageEndEnabled) BOOL scrollOnTapPageEndEnabled;

/// change thumbnail size. Default is 162x200.
@property(nonatomic, assign) CGSize thumbnailSize;

/// change margin around thumbnails. Defaults to 10x10.
@property(nonatomic, assign) CGSize thumbnailMargin;

/// thumbnails on iPhone are smaller - you may change the reduction factor. Defaults to 0.588.
@property(nonatomic, assign) CGFloat iPhoneThumbnailSizeReductionFactor;

/// view that is displayed as HUD. Make a KVO on viewMode if you build a different HUD for thumbnails view.
@property(nonatomic, retain, readonly) UIView *hudView;

/// show or hide HUD controls, titlebar, status bar. (iPhone only)
@property(nonatomic, assign, getter=isHUDVisible) BOOL HUDVisible;

/// animated show or hide HUD controls, titlebar, status bar. (iPhone only)
- (void)setHUDVisible:(BOOL)show animated:(BOOL)animated;

// ****** functions you may wanna override in subclasses ****

/// returns the topmost active viewcontroller. override if you have a custom setup of viewControllers
- (UIViewController *)masterViewController;

/// Class for creating the scroll view. Set this to your custom subclass if you override PSPDFScrollView.
- (Class)scrollViewClass;

/// Class used to create the scrobble bar. Set this to your custom subclass if you override PSPDFScrobbleBar.
- (Class)scrobbleBarClass;

/// override if you're changing the toolbar to your own.
/// Note: The toolbar is only displayed, if PSPDFViewController is inside a UINavigationController.
- (void)createToolbar;

- (UIBarButtonItem *)toolbarBackButton; // defaults to "Documents"

- (NSArray *)additionalLeftToolbarButtons; // not used when not modal

- (void)updateToolbars;

// called from scrollviews
- (void)showControls;
- (void)hideControls;
- (void)toggleControls;
- (NSUInteger)landscapePage:(NSUInteger)aPage;

@end
