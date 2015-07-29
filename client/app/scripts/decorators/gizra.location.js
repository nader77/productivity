'use strict';

/**
 * @ngdoc Module to generate dynamic urls, for locations.
 * @name gizra.location
 * @description
 * # gizra.location
 *
 * Main module of the application, extend the actual $location service.
 */
angular
  .module('gizra.location', [])
  .config(function($provide) {
    $provide.decorator('$location', function($delegate, Config) {

      /**
       * return enviroment where the client application is.
       */
      $delegate.backend = function backend() {
        return Config[Config.enviroments[this.$$host]].backend;
      };

      /**
       * return enviroment where the client application is.
       */
      $delegate.enviroment = function enviroment() {
        return Config.enviroments[this.$$host];
      };

      return $delegate;
    });
  })
