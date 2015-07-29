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
  .module('clientApp')
  .config(function($provide) {
    $provide.decorator('$location', function($delegate, Config) {

      /**
       * Extend service $location to return a backend url, base on options.
       *
       * @param options
       *   {
       *     'urlPattern':  'http//${appname}/${skeleton}',
       *     'appname': 'skeleton',
       *     'domain': 'domain.com'
       *   }
       *
       * @returns {promise|void}
       */
      $delegate.backendDynamic = function backendDynamic() {
        var self = this;
        var uri;

        /**
         * Generate backend URL according the url pattern in options;
         * @param options
         * @returns {*}
         */
        function generateUrlFormTemplate(options) {
          var matches;
          var max;
          var regex = /\${(\w*)}/;

          //uri = Config.urlPattern;
          while ((matches = regex.exec(options.urlPattern)) !== null) {
            options.urlPattern = options.urlPattern.replace(matches[0], Config[self.enviroment()][matches[1]]);
            if (matches.index === regex.lastIndex || max < 10) {
              regex.lastIndex++;
              max++;
            }
          }

          return options.urlPattern;
        }

        // Save initial value of property reloadOnSearch per state.
        try {
          uri = generateUrlFormTemplate(Config[this.enviroment()]);
        }
        catch (e) {
          throw new Error(e);
        }

        return uri || 'http://server/';
      };


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
