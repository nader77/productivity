'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:CompaniesCtrl
 * @description
 * # CompaniesCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('TrackingTableCtrl', function ($scope, tracking, trackingProject, $stateParams, $log, Config) {
    console.log(trackingProject);
    var endDay = new Date($stateParams.year, $stateParams.month, 0).getDate();
    var days = [];
    for (var i = 1; i <= endDay; i++) {
      days.push(i);
    }
    $scope.employeeRows = tracking;

    $scope.year = $stateParams.year;
    $scope.month = $stateParams.month;

    $scope.nextMonth = $scope.month + 1;
    $scope.nextYear =  $scope.year;
    $scope.prevMonth = $scope.month - 1;
    $scope.prevYear =  $scope.year;

    if ($scope.month == 12) {
      $scope.nextMonth = 1;
      $scope.nextYear =  $scope.year + 1;
    }
    if ($scope.month == 1) {
      $scope.prevMonth = 12;
      $scope.prevYear =  $scope.year - 1;
    }


    $scope.days = days;

    if (Config.debug) {
      console.log($scope.employeeRows);
    }

  });
