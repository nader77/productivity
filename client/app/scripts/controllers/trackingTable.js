'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:CompaniesCtrl
 * @description
 * # CompaniesCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('TrackingTableCtrl', function ($scope, tracking, $stateParams, $log) {

    // Initialize values.
    $scope.tracking = tracking;
    $scope.selectedTrack = null;
    $scope.year = $stateParams.year;
    $scope.month = $stateParams.month;

    $scope.days = tracking.days;


    $scope.employeeRows = tracking.data;// prepareEmployeeJson(tracking, $scope.days);
  });
