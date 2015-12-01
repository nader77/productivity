Feature: Login test
  Test login and default actions.

  @api
  Scenario: Check access denied when not logged in.
    Given I visit the homepage
    Then  I see the text "Access denied"


  @api
  Scenario: Attempt login.
    Given I am logged in as a user with the "authenticated" role
    When  I visit the homepage
    Then  I should see the text "My account"
