'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:HomepageCtrl
 * @description
 * # HomepageCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('HomepageCtrl', function ($scope, $state, account, $log) {
    if (account) {
      $state.go('dashboard.tracking-table', {
        year: 2014,
        month: 11
      });
    }
    else {
      // Redirect to login.
      $state.go('login');
    }
  });
