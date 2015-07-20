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
  .module('gizra.location', [
    'config'
  ])
  .config(function($provide) {
    $provide.decorator('$location', function($delegate) {

      /**
       * Extend service $location to return a backend url, base on options.
       *
       * @param options
       *   {
       *     'appname': Config.appname,
       *     'domain': Config.domain,
       *     'local': Config.local
       *   }
       *
       * @returns {promise|void}
       */
      $delegate.backend = function backend(options) {
        var uri;

        /**
         * Generate backend URL according the url pattern in options;
         * @param options
         * @returns {*}
         */
        function generateUrlFormTemplate(options) {
          var regex = /\${(\w*)}/;

          while ((matches = regex.exec(option.urlPattern)) !== null) {
            debugger;
            if (matches.index === regex.lastIndex) {
              regex.lastIndex++;
            }
            // View your result using the m-variable.
            // eg m[0] etc.
          }

          return uri;
        }

        /**
         * Binding element with options values.
         *
         * @param element
         * @param options
         *
         * @returns {*}
         */
        function bindElement(element, options) {
          switch(element) {
            case 'host':
              return this.host();
              break;
            default:
              return options[element];
              break;
          }
        }

        // Save initial value of property reloadOnSearch per state.
        return generateUrlFormTemplate(options);
      };

      return $delegate;
    });
  })
  .run(function(Config, $location) {
    // Is possible uyse $location service with $http request intead Confir.url
    Config.backend = $location.backend(Config);

    console.log('gizra.location backend: ', Config.backend);
  })
