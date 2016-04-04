/**
 * @ngdoc function
 * @name clientApp.controller:GithubAuthCtrl
 * @description
 * # GithubAuthCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('GithubAuthCtrl', function ($scope, $state, Auth, $window, localStorageService) {
    // get the code.
    var code = $window.location.search.replace('?code=', '');

    Auth.authByGithubCode(code)
    .then(function() {
      // Login was ok.
      $state.go('homepage');
    })
      .catch(function(data) {
        localStorageService.set('loginErrorMessage', data.data.title);
        $state.go('login');
      });
  });

'use strict';
