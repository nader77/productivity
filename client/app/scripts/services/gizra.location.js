'use strict';

/**
 * @ngdoc Module to generate dynamic urls, for locations.
 * @name gizra.location
 * @description
 * # gizra.location
 *
 * Main module of the application.
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
       * @returns {promise|void}
       */
      $delegate.backend = function backend(options) {
        var url;

        // local
        if (options.local) {
          url = this.protocol()
            + '://'
            + this.host()
            + '/'
            + options.appname;
            + '/www'
        }
        else {
          // hosting ()
          url = this.protocol()
            + '://'
            + options.appname;
            + '.'
            + this.host()
        }

        // Save initial value of property reloadOnSearch per state.
        return url;
      };

      return $delegate;
    });
  })
  .run(function(Config, $location) {
    debugger;
    Config.backend = $location.backend({
      'appname': Config.appname,
      'domain': Config.domain,
      'local': Config.local
    });
    // If we're not on a local env, take the backend url for base URL.
    // if (!Config.local) {
    //   Config.backend = window.location.protocol + '//' +  window.location.host + '/';
    // }
    console.log('gizra.location', Config);
  })
