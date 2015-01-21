'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:CompaniesCtrl
 * @description
 * # CompaniesCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('TrackingTableCtrl', function ($scope, tracking, $stateParams, $log, Config) {

    var endDay = new Date($stateParams.year, $stateParams.month, 0).getDate();
    var days = [];
    for (var i = 1; i <= endDay; i++) {
      days.push(i);
    }
    $scope.employeeRows = tracking;

    $scope.year = $stateParams.year;
    $scope.month = $stateParams.month;

    $scope.days = days;

    if (Config.debug) {
      console.log($scope.employeeRows);
    }

  });
