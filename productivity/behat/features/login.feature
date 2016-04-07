Feature: Login test
  Test login and default actions.

  @api
  Scenario: Check access denied when not logged in.
    Given I visit the homepage
    Then  I see the text "Access denied"


  @api
  Scenario: Attempt login.
    Given I login with user "admin"
    When  I visit the homepage
    Then  I should see the text "Dashboard"
