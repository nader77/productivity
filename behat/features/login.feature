Feature: Login to app
  In order to be able to access content
  As an anonymous user
  We need to be able to login to the site and be authenticated

  @javascript
    Scenario: Login to the back server
    Given I am an anonymous user
    When I login the user "admin"
    Then I should check the url for "admin"
