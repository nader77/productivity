Feature: Time tracking
  when add or editing or deleting tracking, I should see
  the total tracking on the project page is updated accordingly

  @javascript
  Scenario: Adding a new tracking entry
    Given I login with user "admin"
    When  I get the total hours from "nike-site" project
    And   I add a new time tracking to the issue "Giant Bug" with "3" hours to "nike Site" project
    Then  I validate that total hours have "incremented" by "3"

  @api
  Scenario: Editing an existing tracking entry
    Given I login with user "admin"
    When  I get the total hours from "nike-site" project
    And   I add "3" hours to the latest tracking entry
    Then  I validate that total hours have "incremented" by "3"

  @api
  Scenario: Deleting an tracking entry
    Given I login with user "admin"
    When  I get the total hours from "nike-site" project
    And   I delete the latest tracking entry
    Then  I validate that total hours have "decremented" by "6"
