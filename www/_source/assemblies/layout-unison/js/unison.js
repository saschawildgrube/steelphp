/*
 * Unison Material Design Portfolio Template
 * Copyright 2016 8Guild.com
 * Theme Custom Scripts
 */
 /* ╔══╗╔═══╗╔╗╔╗╔══╗╔╗──╔══╗
  	║╔╗║║╔══╝║║║║╚╗╔╝║║──║╔╗╚╗
  	║╚╝║║║╔═╗║║║║─║║─║║──║║╚╗║
  	║╔╗║║║╚╗║║║║║─║║─║║──║║─║║
  	║╚╝║║╚═╝║║╚╝║╔╝╚╗║╚═╗║╚═╝║
  	╚══╝╚═══╝╚══╝╚══╝╚══╝╚═══╝
*/

jQuery(document).ready(function($) {
	'use strict';

	// Disable default link behavior for dummy links that have href='#'
	var $emptyLink = $('a[href=#]');
	$emptyLink.on('click', function(e){
		e.preventDefault();
	});

	// Page Transitions
	$('a:not([href^=#])').on('click', function(e) {
    if($(this).attr('class') !== 'gallery-tile' && $(this).attr('class') !== 'play-btn') {
      e.preventDefault();
      var linkUrl = $(this).attr('href');
      $('.page-preloading').addClass('link-clicked');
      setTimeout(function(){
        window.open(linkUrl , '_self');
      }, 550);
    }
  });

	// Stuck navbar on scroll
	if($('.header-sticky').length) {
		var sticky = new Waypoint.Sticky({
		  element: $('.header-sticky .navbar')[0]
		});
	}

	// Mobile Menu
	var $mobileMenuToggle = $('.mobile-menu-toggle'),
			$mobileMenu = $('.main-navigation');
	$mobileMenuToggle.on('click', function() {
		$(this).toggleClass('menu-close');
		$mobileMenu.toggleClass('open');
	});

	// Mobile Submenu
	var $mobileSubmenuToggle = $('.menu-item-has-children');
	$mobileSubmenuToggle.on('click', function() {
		$(this).toggleClass('active');
	});


	/* Floating Menu
	**************************************************************/

 	var $floatingMenuToggle = $('.floating-menu-toggle-wrap'),
			$floatingMenu = $('.floating-header .main-navigation'),
			$floatingMenuItem = $('.floating-header .main-navigation .menu > li');
	if($floatingMenu.length) {
		$floatingMenuItem.each(function(index, element) {
			$(element).addClass('delay-' + index);
		});

		$floatingMenuToggle.click(function() {
		  var clicks = $(this).data('clicks');
		  if (clicks) {
				$floatingMenu.removeClass('is-visible');
				setTimeout(function(){
					$floatingMenuToggle.parent().removeClass('expanded');
				}, 500);
		  } else {
				$floatingMenuToggle.parent().addClass('expanded');
				$floatingMenu.addClass('is-visible');
		  }
		  $(this).data("clicks", !clicks);
		});

	}

	// Back Button
	var backBtnText = $floatingMenu.data( 'back-btn-text' ),
			subMenu = $( '.floating-header .main-navigation .sub-menu' );

	subMenu.each( function () {
		$( this ).prepend( '<li class="back-btn"><a href="#">' + backBtnText + '</a></li>' );
	} );

	var hasChildLink = $( '.floating-header .menu-item-has-children > a' ),
		backBtn = $( '.floating-header .main-navigation .sub-menu .back-btn' );

	backBtn.on('click', function (e) {
		var self = this,
			parent = $( self ).parent(),
			siblingParent = $( self ).parent().parent().siblings().parent(),
			menu = $( self ).parents( '.menu' );

		parent.removeClass( 'in-view' );
		siblingParent.removeClass( 'off-view' );

		e.stopPropagation();
	});

	hasChildLink.on( 'click', function ( e ) {
		var self = this,
			parent = $( self ).parent().parent(),
			menu = $( self ).parents( '.menu' );

		parent.addClass( 'off-view' );
		$( self ).parent().find( '> .sub-menu' ).addClass( 'in-view' );

		e.preventDefault();
		return false;
	} );

	/******************************************************************/


	// Waves Effect (on Buttons)
	if($('.waves-effect').length) {
		Waves.displayEffect( { duration: 600 } );
	}

	// Material Effect on Inputs
	var $input = $('.form-input input, .form-input textarea');
	$input.on('focus', function(){
		if (this.value === '') {
			$(this).parent().addClass('active');
		}
	});
	$input.on('blur', function(){
		if (this.value === '') {
			$(this).parent().removeClass('active');
		}
	});

	// Animated Scroll to Top Button
	var $scrollTop = $('.scroll-to-top-btn');
	if ($scrollTop.length > 0) {
		$(window).on('scroll', function(){
	    if ($(window).scrollTop() > 600) {
	      $scrollTop.addClass('visible');
	    } else {
	      $scrollTop.removeClass('visible');
	    }
		});
		$scrollTop.on('click', function(e){
			e.preventDefault();
			$('html').velocity("scroll", { offset: 0, duration: 1000, easing:'easeOutExpo', mobileHA: false });
		});
	}

	// Smooth scroll to element
	var $scrollTo = $('.scroll-to');
	$scrollTo.on('click', function(event){
		var $elemOffsetTop = $(this).data('offset-top') || 150;
		$('html').velocity("scroll", { offset:$(this.hash).offset().top-$elemOffsetTop, duration: 1000, easing:'easeOutExpo', mobileHA: false});
		event.preventDefault();
	});

	// Tooltips
	var $tooltip = $('[data-toggle="tooltip"]');
	if ($tooltip.length) {
		$tooltip.tooltip();
	}

	// Counters (Animated Digits)
	function counterOnScrollAnimation( items, trigger ) {
	  items.each( function() {
	    var counterElement = $(this),
	        duration = $(this).data('duration');

	    var counterTrigger = ( trigger ) ? trigger : counterElement;

	    counterTrigger.waypoint(function(direction) {
				  	if(direction == 'down') {
			      	counterElement.find('.digits').spincrement({
									from: 0.0,
									duration: duration
							});
				  	} else {
				  		this.destroy();
				  	}
	    },{
	        offset: '95%'
	    });
	  });
	}
	counterOnScrollAnimation( $('.counter') );

	// Custom Scrollbar
	var $sidebarScroll = $('.sidebar > .scroll-area');
	if($sidebarScroll.length) {
		$sidebarScroll.mCustomScrollbar({
			theme: 'dark'
		});
	}

	// Sidebar Toggle
	var $sidebar = $('.sidebar'),
			$sidebarBackdrop = $('.sidebar-backdrop');
	$('.sidebar-toggle').on('click', function(){
		$sidebar.addClass('expanded');
		$sidebarBackdrop.addClass('visible');
	});
	$('.sidebar-close, .sidebar-backdrop').on('click', function(){
		$sidebar.removeClass('expanded');
		$sidebarBackdrop.removeClass('visible');
	});

	// Post Sharing Toggle
	$('.sharing-toggle').on('click', function(){
		$(this).parent().toggleClass('expanded');
	});


	// On window load functions
	$(window).on('load', function(){

		// Isotope Grid
		var $grid = $('.isotope-masonry-grid, .isotope-grid');
		if($grid.length > 0) {
		  $grid.isotope({
			  itemSelector: '.grid-item',
			  transitionDuration: '0.7s',
			  masonry: {
			    columnWidth: '.grid-sizer',
			    gutter: '.gutter-sizer'
			  }
		  });
		}

		// Filtering
		if($('.filter-grid').length > 0) {
		  var $filterGrid = $('.filter-grid');
			$('.nav-filters').on( 'click', 'a', function(e) {
				e.preventDefault();
				$('.nav-filters li').removeClass('active');
				$(this).parent().addClass('active');
			  var $filterValue = $(this).attr('data-filter');
			  $filterGrid.isotope({ filter: $filterValue });
			});
		}

		/** Background Parallax **/
		if ( ! Modernizr.touch && ! $('html.ie').length ) {
			if ( $( "body.parallax" ).length > 0 ) {
				$.stellar( {
					scrollProperty: 'scroll',
					verticalOffset: 0,
					horizontalOffset: 0,
					horizontalScrolling: false,
					responsive: true
				} );
			}
		}

	});

	// Scroll Reveal Animations
	if($('.scrollReveal').length && ! $('html.ie9').length) {
		$('.scrollReveal').parent().css('overflow', 'hidden');
		window.sr = ScrollReveal({
			reset: true,
			distance: '32px',
			mobile: true,
			duration: 850,
			scale: 1,
			viewFactor: 0.3,
			easing: 'ease-in-out'
		});
		sr.reveal('.sr-top', { origin: 'top' });
		sr.reveal('.sr-bottom', { origin: 'bottom' });
		sr.reveal('.sr-left', { origin: 'left' });
		sr.reveal('.sr-long-left', { origin: 'left', distance: '70px', duration: 1000 });
		sr.reveal('.sr-right', { origin: 'right' });
		sr.reveal('.sr-scaleUp', { scale: '0.8' });
		sr.reveal('.sr-scaleDown', { scale: '1.15' });

		sr.reveal('.sr-delay-1', { delay: 200 });
		sr.reveal('.sr-delay-2', { delay: 400 });
		sr.reveal('.sr-delay-3', { delay: 600 });
		sr.reveal('.sr-delay-4', { delay: 800 });
		sr.reveal('.sr-delay-5', { delay: 1000 });
		sr.reveal('.sr-delay-6', { delay: 1200 });
		sr.reveal('.sr-delay-7', { delay: 1400 });
		sr.reveal('.sr-delay-8', { delay: 1600 });

		sr.reveal('.sr-ease-in-out-quad', { easing: 'cubic-bezier(0.455,  0.030, 0.515, 0.955)' });
		sr.reveal('.sr-ease-in-out-cubic', { easing: 'cubic-bezier(0.645,  0.045, 0.355, 1.000)' });
		sr.reveal('.sr-ease-in-out-quart', { easing: 'cubic-bezier(0.770,  0.000, 0.175, 1.000)' });
		sr.reveal('.sr-ease-in-out-quint', { easing: 'cubic-bezier(0.860,  0.000, 0.070, 1.000)' });
		sr.reveal('.sr-ease-in-out-sine', { easing: 'cubic-bezier(0.445,  0.050, 0.550, 0.950)' });
		sr.reveal('.sr-ease-in-out-expo', { easing: 'cubic-bezier(1.000,  0.000, 0.000, 1.000)' });
		sr.reveal('.sr-ease-in-out-circ', { easing: 'cubic-bezier(0.785,  0.135, 0.150, 0.860)' });
		sr.reveal('.sr-ease-in-out-back', { easing: 'cubic-bezier(0.680, -0.550, 0.265, 1.550)' });
	}

	// Image Carousel
	var $imageCarousel = $('.image-carousel .inner');
	if ($imageCarousel.length > 0) {
		$imageCarousel.each( function () {
			var nextBtn = $(this).find('.owl-next'),
					prevBtn = $(this).find('.owl-prev'),
					loop = $(this).parent().data('loop'),
					autoplay = $(this).parent().data('autoplay'),
					interval = $(this).parent().data('interval') || 3000,
					autoheight = $(this).parent().data('autoheight');

			$(this).owlCarousel({
				items: 1,
				loop: loop,
				margin: 0,
				nav: true,
				dots: false,
				navText: [ , ],
				autoplay: autoplay,
				autoplayTimeout: interval,
				autoHeight: autoheight
			}).on('changed.owl.carousel', function(event) {
				var curItem = event.item.index + 1,
						items = event.item.count;
				if(curItem === items && !loop) {
					$(this).find(nextBtn.selector).css({'visibility': 'hidden', 'opacity':'0'});
					$(this).find(prevBtn.selector).css({'visibility': 'visible', 'opacity':'1'});
				} else if(curItem === 1 && !loop) {
					$(this).find(nextBtn.selector).css({'visibility': 'visible', 'opacity':'1'});
					$(this).find(prevBtn.selector).css({'visibility': 'hidden', 'opacity':'0'});
				}
			});
		});
	}

	// Fullscreen Slideshow
	var $fwSlideshow = $('.fullscreen-slideshow'),
			$thumblist = $('.fullscreen-slideshow .thumbnails-list .inner ul'),
			$thumbnail = $thumblist.find('li > a'),
			$slideshowImg = $('.fullscreen-slideshow .bg-image li');
	if($fwSlideshow.length) {
		$thumblist.each(function() {
			$(this).owlCarousel({
				margin: 0,
				nav: false,
				dots: false,
				responsive: {
					0: { items: 1 },
					480: { items: 2 },
					800: { items: 3 },
				}
			});
		});
		$thumbnail.on('click', function(e) {
			var imgID = $(this).attr('href');
			$thumbnail.parent().removeClass('active');
			$(this).parent().addClass('active');
			$slideshowImg.removeClass('current');
			$(imgID).addClass('current');
			e.preventDefault();
		});
	}

	// Testimonials Carousel
	var $testimonialsCarousel = $( '.testimonials-carousel .inner' );
	if ( $testimonialsCarousel.length > 0 ) {
		$testimonialsCarousel.each( function () {
			var nextBtn = $(this).find('.owl-next'),
					prevBtn = $(this).find('.owl-prev'),
					slide = $(this).find('.owl-item'),
					authorImg = $(this).parents('.testimonials-carousel').find('.author-img span'),
					loop = $(this).parents('.testimonials-carousel').data('loop'),
					autoplay = $(this).parents('.testimonials-carousel').data('autoplay'),
					interval = $(this).parents('.testimonials-carousel').data('interval') || 3000;

			$( this ).owlCarousel({
				items: 1,
				loop: loop,
				margin: 10,
				nav: true,
				dots: false,
				navText: [ , ],
				autoplay: autoplay,
				autoplayTimeout: interval,
				autoHeight: true,
			}).on('changed.owl.carousel', function(event) {
				var curItemIndex = event.item.index,
						curItem = curItemIndex + 1,
						item = event.item.count,
						items = $(slide.selector),
						currentAuthorImg = $(items[curItemIndex]).find('blockquote').data('author-id');
				authorImg.removeClass('active');
				$('#' + currentAuthorImg).addClass('active');
				if(curItem === item && !loop) {
					$(this).find(nextBtn.selector).css({'visibility': 'hidden', 'opacity':'0'});
					$(this).find(prevBtn.selector).css({'visibility': 'visible', 'opacity':'1'});
				} else if(curItem === 1 && !loop) {
					$(this).find(nextBtn.selector).css({'visibility': 'visible', 'opacity':'1'});
					$(this).find(prevBtn.selector).css({'visibility': 'hidden', 'opacity':'0'});
				}
			});
		});
	}

	// Timeline
	var $timeline = $( '.timeline .inner' );
	if ( $timeline.length > 0 ) {
		$timeline.each( function () {

			$(this).owlCarousel({
				loop: false,
				margin: 0,
				nav: true,
				dots: false,
				responsiveClass: true,
				responsive: {
					0: { items: 1 },
					480: { items: 2 },
					800: { items: 3 },
					1200: { items: 4 },
				}
			});
		});
	}

	// Hero Carousel
	var $heroCarousel = $( '.hero-carousel .inner' );
	if ( $heroCarousel.length > 0 ) {
		$heroCarousel.each( function () {

		var	loop = $(this).parent().data('loop'),
				autoplay = $(this).parent().data('autoplay'),
				interval = $(this).parent().data('interval') || 3000;

			$(this).owlCarousel({
				items: 1,
				loop: loop,
				margin: 0,
				nav: true,
				dots: false,
				autoplay: autoplay,
				autoplayTimeout: interval,
				autoplayHoverPause: true,
				smartSpeed: 450
			});
		});
	}

	// Gallery Popup
	var $gallItem = $( '.gallery-tile' );
	if( $gallItem.length > 0 ) {
		$gallItem.magnificPopup( {
		  type: 'image',
		  mainClass: 'mfp-fade',
		  gallery: {
		    enabled: true
		  },
		  removalDelay: 500,
		  image: {
		  	titleSrc: 'data-title'
		  }
		} );
	}

	// Video Popup
	var $videoBtn = $( '.video-popup-btn > .play-btn' );
	if( $videoBtn.length > 0 ) {
		$videoBtn.magnificPopup( {
		  type: 'iframe',
		  mainClass: 'mfp-fade',
		  removalDelay: 500
		} );
	}


	// Google Maps API
	var $googleMap = $('.google-map');
	if($googleMap.length > 0) {
		$googleMap.each(function(){
			var mapHeight = $(this).data('height'),
					address = $(this).data('address'),
					zoom = $(this).data('zoom'),
					controls = $(this).data('disable-controls'),
					scrollwheel = $(this).data('scrollwheel'),
					marker = $(this).data('marker'),
					markerTitle = $(this).data('marker-title'),
					styles = $(this).data('styles');
			$(this).height(mapHeight);
			$(this).gmap3({
          marker:{
            address: address,
            data: markerTitle,
            options: {
            	icon: marker
            },
            events: {
              mouseover: function(marker, event, context){
                var map = $(this).gmap3("get"),
                  	infowindow = $(this).gmap3({get:{name:"infowindow"}});
                if (infowindow){
                  infowindow.open(map, marker);
                  infowindow.setContent(context.data);
                } else {
                  $(this).gmap3({
                    infowindow:{
                      anchor:marker,
                      options:{content: context.data}
                    }
                  });
                }
              },
              mouseout: function(){
                var infowindow = $(this).gmap3({get:{name:"infowindow"}});
                if (infowindow){
                  infowindow.close();
                }
              }
            }
          },
          map:{
            options:{
              zoom: zoom,
              disableDefaultUI: controls,
              scrollwheel: scrollwheel,
              styles: styles
            }
          }
			});
		});
	}

});/*Document Ready End*/
