'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:HomepageCtrl
 * @description
 * # HomepageCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('HomepageCtrl', function ($scope, $state, account) {
    if (account) {
      var today = new Date();
      var dd = today.getDate();
      var mm = today.getMonth()+1; //January is 0!
      var yyyy = today.getFullYear();

      $state.go('dashboard.tracking-form', {
        username: account.label,
        year: yyyy,
        month: mm,
        day: dd,
        id: 'new'
      });
    }
    else {
      // Redirect to login.
      $state.go('login');
    }
  });
