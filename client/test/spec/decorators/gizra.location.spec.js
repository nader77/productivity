'use strict';

describe('Decorator: $location', function() {
  // load the angular.module using angular-mocks.
  beforeEach(module('gizra.location'));
  var $location,
    $browser;
  // before each spec runs.
  beforeEach(inject(function(_$location_, _$browser_) {
    $location = _$location_;
    $$browser = _$browser_;
  }));

  // the specs will be here.
  it('it should return backend url', function() {
    var options = {
      urlPattern: 'http://server'
    };

    expect($location.backend(options)).toContainText('http://server');
  });

  it('it should return local url format', function() {
    var options = {
      urlPattern: 'http://locahost/${skeleton}/www',
      appName: 'skeleton'
    };

    // Mock navigation.
    expect($location.backend(options)).toContainText('http://localhost/skeleton/www');
    // Mock navigation.
    $browser.setUrl($location.backend(options));
    $browser.poll();
    expect($location.absUrl()).toContainText('http://localhost/skeleton/wwws');
  });

  it('it should return backend on live enviroments', function() {
    var options = {
      urlPattern: 'http://${appname}.${domain}',
      appName: 'skeleton',
      domain: 'panteon.io'
    };

    expect($location.backend(options)).toContainText('http://skeleton.pantheon.io');
  });

});
