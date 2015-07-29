'use strict';

/**
 * @ngdoc Module to generate backend from a config file.
 * @name gizra.config
 * @description
 * # gizra.config
 *
 */
angular
  .module('gizra.config')
  .provider('Config', function() {

    function Config(configFile, $location) {

      // Return backend url.
      this.backend = backend();

      /**
       * return backend url according the enviroment.
       */
      function backend() {
        return configFile[configFile.enviroments[$location.host()]].backend;
      };

      /**
       * return enviroment where the client application is.
       */
      function enviroment() {
        return configFile.enviroments[$location.host()];
      };

    }

    this.$get = ['configFile', '$location', function(configFile, $location) {
      return new Config(configFile, $location);
    }];

  });
