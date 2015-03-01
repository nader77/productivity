'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:DashboardCtrl
 * @description
 * # DashboardCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('DashboardCtrl', function ($scope, Auth, $state, account, $log) {

    var today = new Date();
    $scope.day = today.getDate();
    //January is 0!
    $scope.month = today.getMonth()+1;
    $scope.year = today.getFullYear();
    $scope.employee = account.label;

    $scope.spinner = 0;

    $scope.$on('$stateChangeStart', function(event, toState, toParams, fromState, fromParams) {
      if (toState.resolve) {
        $scope.toggleSpinner();
      }
    });
    $scope.$on('$stateChangeSuccess', function(event, toState, toParams, fromState, fromParams) {
      if (toState.resolve) {
        $scope.toggleSpinner();
      }
    });

    /**
     *
     */
    $scope.toggleSpinner = function() {

    };

    /**
     * Logout current user.
     *
     * Do whatever cleaning up is required and change state to 'login'.
     */
    $scope.logout = function() {
      Auth.logout();
      $state.go('login');
    };
  });
