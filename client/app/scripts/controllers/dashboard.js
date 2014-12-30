'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:DashboardCtrl
 * @description
 * # DashboardCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('DashboardCtrl', function ($scope, Auth, $state, $log) {

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
