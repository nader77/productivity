'use strict';

describe('Decorator: $location', function() {
  var $location,
    $browser;
  // load the angular.module using angular-mocks.
  beforeEach(function () {
    module(
      'ng',
      'ngMock',
      'gizra.location'
    );

    inject(function(_$location_) {
      $location = _$location_;
    });
  });

  it('it should be true', function() {
    expect(true).toBe(true);
  });

  //// the specs will be here.
  //it('it should return backend url', function() {
  //  var options = {
  //    urlPattern: 'http://server'
  //  };
  //  Config = options;
  //
  //  expect($location.backend(options)).toContain('http://server');
  //});
  //
  //it('it should return local url format', function() {
  //  var options = {
  //    urlPattern: 'http://locahost/${skeleton}/www',
  //    appName: 'skeleton'
  //  };
  //
  //  // Mock navigation.
  //  expect($location.backend(options)).toContainText('http://localhost/skeleton/www');
  //  // Mock navigation.
  //  $browser.setUrl($location.backend(options));
  //  $browser.poll();
  //  expect($location.absUrl()).toContainText('http://localhost/skeleton/wwws');
  //});
  //
  //it('it should return backend on live enviroments', function() {
  //  var options = {
  //    urlPattern: 'http://${appname}.${domain}',
  //    appName: 'skeleton',
  //    domain: 'panteon.io'
  //  };
  //
  //  expect($location.backend(options)).toContainText('http://skeleton.pantheon.io');
  //});

});
