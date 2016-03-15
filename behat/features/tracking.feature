Feature: Time tracking
  When add or editing or deleting tracking, I should see
  the total tracking on the project page is updated accordingly

  @api
  Scenario: Add a new tracking
    Given I login with user "avi"
     Then I get the total hours
     Then I add a new time tracking entry
    And I validate the total hours
