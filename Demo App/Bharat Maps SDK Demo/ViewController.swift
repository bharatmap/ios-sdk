//
//  ViewController.swift
//  Bharat Maps SDK Demo
//
//  Created by Ivan Nikolaev on 31.03.2026.
//

import UIKit
import BharatMaps

class ViewController: UIViewController, BharatMapsMapViewDelegate {
    
    // Hints view
    @IBOutlet private var placeholderView: UIStackView!

    // Map UI elements
    @IBOutlet private var controlsContainerView: UIView!
    @IBOutlet private var mapView: BharatMapView!
    @IBOutlet private var locationButton: BharatMapsLocationButton!
    @IBOutlet private var zoomControls: BharatMapsZoomControl!
    
    // Reverse geocoding popup
    @IBOutlet private var reverseGeocodingResultPopupView: UIView!
    @IBOutlet private var reverseGeocodingPlaceAddressLabel: UILabel!
    @IBOutlet private var reverseGeocodingPlaceCoordinatesLabel: UILabel!
    @IBOutlet private var reverseGeocodingButtonFrom: UIButton!
    @IBOutlet private var reverseGeocodingButtonTo: UIButton!
    
    // Navigation progress UI elements
    @IBOutlet private var routeSelector: BharatMapsRouteSelector!
    @IBOutlet private var routeSelectorContainer: UIStackView!
    @IBOutlet private var navigationProgressView: UIStackView!
    @IBOutlet private var nextRoadNameLabel: BharatMapsNextRoadNameLabel!
    @IBOutlet private var speedLabel: BharatMapsSpeedLabel!
    @IBOutlet private var maneuverSign: BharatMapsManeuverSign!
    @IBOutlet private var maneuverDistanceLabel: BharatMapsManeuverDistanceLabel!
    @IBOutlet private var tripTimeRemainingLabel: BharatMapsTripTimeRemainingLabel!
    @IBOutlet private var tripTimeArrivalLabel: BharatMapsTripTimeArrivalLabel!
    @IBOutlet private var tripDistanceLabel: BharatMapsTripDistanceLabel!
//    @IBOutlet private var tripEndView: BharatMapsTripEndView!

    // MARK: - Lifecycle
    override func viewDidLoad() {
        super.viewDidLoad()

        setupMap()
        setupUI()
    }
    
    // MARK: - UI Setup
    private func setupUI() {
        
        self.routeSelectorContainer.isHidden = true
        
        controlsContainerView.backgroundColor = .white
        controlsContainerView.layer.shadowColor = UIColor.black.cgColor
        controlsContainerView.layer.shadowRadius = 20.0
        controlsContainerView.layer.shadowOpacity = 0.2
        
        locationButton.cornerRadius = 30.0
        locationButton.layer.shadowColor = UIColor.black.cgColor
        locationButton.layer.shadowRadius = 15.0
        locationButton.layer.shadowOpacity = 0.2
        locationButton.layer.shadowOffset = CGSize(width: 0.0, height: 10.0)
        
        zoomControls.cornerRadius = 30.0
        zoomControls.layer.shadowColor = UIColor.black.cgColor
        zoomControls.layer.shadowRadius = 15.0
        zoomControls.layer.shadowOpacity = 0.2
        zoomControls.layer.shadowOffset = CGSize(width: 0.0, height: 10.0)
        
        speedLabel.cornerRadius = 30.0
        speedLabel.layer.shadowColor = UIColor.black.cgColor
        speedLabel.layer.shadowRadius = 15.0
        speedLabel.layer.shadowOpacity = 0.2
        speedLabel.layer.shadowOffset = CGSize(width: 0.0, height: 10.0)
    }

    private func setupMap() {
        mapView.delegate = self
        mapView.defaultZoom = 16.0
        mapView.defaultLocation = CLLocationCoordinate2D(latitude: 26.86112024047445, longitude: 75.79514297855094)
        mapView.validateLicense(apiKey: "YOUR_BHARATMAPS_API_KEY") { result, error in
            if let error {
                print("license error: \(error.localizedDescription)")
            } else {
                print("license ok token=" + ((result?["token"] as? String) ?? "") + "")
            }
        }
        mapView.enableUserLocation()
        
        // Navigation instructions
        nextRoadNameLabel.bharatMapView = mapView
        speedLabel.bharatMapView = mapView
        maneuverSign.bharatMapView = mapView
        maneuverDistanceLabel.bharatMapView = mapView
        tripTimeRemainingLabel.bharatMapView = mapView
        tripTimeArrivalLabel.bharatMapView = mapView
        tripDistanceLabel.bharatMapView = mapView

        // Route selector
        routeSelector.bharatMapView = mapView
        routeSelector.backgroundColor = .clear
        routeSelector.font = UIFont.systemFont(ofSize: 19, weight: .semibold)
        
        setupNavigationVisibilityBinding()
    }

    private func setupNavigationVisibilityBinding() {
        mapView.bindNavigationVisibility(placeholderView, visibleWhenNavigationActive: false)
        mapView.bindNavigationVisibility(navigationProgressView, visibleWhenNavigationActive: true)
    }
    

    // MARK: - BharatMapView Delegate stubs
    func bharatMapView(_ bharatMapView: BharatMapView, didTapPoi poi: BharatMapsPoiResult) {
        // stub
    }
    func bharatMapView(_ bharatMapView: BharatMapView, didTapBuildingNumber buildingNumber: BharatMapsBuildingNumberResult) {
        // stub
    }
    func bharatMapView(_ bharatMapView: BharatMapView, didTapUPin uPin: BharatMapsUPinResult) {
        // stub
    }
    func bharatMapView(_ bharatMapView: BharatMapView, didReceiveReverseGeocoding result: BharatMapsReverseGeocodingResult) {
        let coordinate = result.location
        
        reverseGeocodingPlaceAddressLabel.text = result.address
        reverseGeocodingPlaceAddressLabel.isHidden = result.address == nil
        reverseGeocodingPlaceCoordinatesLabel.text = String(format: "%.6f, %.6f", coordinate.latitude, coordinate.longitude)
        
        reverseGeocodingButtonTo.removeTarget(nil, action: nil, for: .allEvents)
        reverseGeocodingButtonTo.addAction(UIAction { _ in
            self.navigationTo(destination: coordinate)
        }, for: .touchUpInside)

        let options = BharatMapsAdvancedAnnotationOptions.default()
        options.persistent = false
        options.backgroundColor = .white
        options.borderColor = UIColor(white: 0.75, alpha: 1.0)
        options.borderWidth = 1
        options.cornerRadius = 12
        options.tailWidth = 32
        options.tailHeight = 22
        options.contentInsets = UIEdgeInsets(top: 12, left: 12, bottom: 12, right: 12)
        options.maxWidth = 300
        options.closeTapOutside = true

        mapView.addAdvancedAnnotation(
            id: "reverse_geocoding_preview",
            location: coordinate,
            content: reverseGeocodingResultPopupView,
            options: options
        )
    }
    func bharatMapView(_ bharatMapView: BharatMapView, didFailReverseGeocodingWithError message: String, location: CLLocationCoordinate2D) {
        // stub
    }
    func bharatMapView(_ bharatMapView: BharatMapView, didUpdate progress: BharatMapsTripProgress) {
        // stub
    }
    func bharatMapView(_ bharatMapView: BharatMapView, didReceiveRoutes routes: [BharatMapsRouteOption]) {
        print("DID RECEIVE ROUTES!")
        self.routeSelectorContainer.isHidden = false
        self.placeholderView.isHidden = true
    }
    
    // MARK: - Navigation
    @objc func navigationTo(destination: CLLocationCoordinate2D) {
        mapView.requestRoutes(destination: destination) { routes, error in
            if let error {
                print("requestRoutes error: \(error.localizedDescription)")
                return
            }
        }
        
        mapView.removeAdvancedAnnotation(id: "reverse_geocoding_preview")
    }

    @IBAction func startNavigation(_ sender: UIButton) {
        mapView.startSelectedNavigation(simulation: true) { error in
            if let error {
                print("startSelectedNavigation error: \(error.localizedDescription)")
            }
            self.routeSelectorContainer.isHidden = true
        }
    }
    @IBAction func stopNavigation(_ sender: UIButton) {
        mapView.stopNavigation()
        self.routeSelectorContainer.isHidden = true
        self.placeholderView.isHidden = false
    }
}
