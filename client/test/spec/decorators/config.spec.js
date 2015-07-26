'use strict';

describe('Config: ', function() {
  // load the angular.module using angular-mocks.
  beforeEach(module('config'));

  var Config;

  beforeEach(inject(function(_Config_) {
    Config = _Config_;
  }));

  it('it should be defined', function() {
    expect(Config).toBeDefined();
  });
});
