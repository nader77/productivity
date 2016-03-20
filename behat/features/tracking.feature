Feature: Time tracking
  When add or editing or deleting tracking, I should see
  the total tracking on the project page is updated accordingly

  Scenario: Adding a new tracking entry
    Given I login with user "avi"
     Then I get the total hours from "nike-site" project
     Then I add a new time tracking entry with "3" hours
      And I validate that total hours have "incremented" by "3"

  Scenario: Editing an existing tracking entry
    Given I login with user "avi"
     Then I get the total hours from "nike-site" project
     Then I add "3" hours to the latest tracking entry
      And I validate that total hours have "incremented" by "3"

  Scenario: Deleting an tracking entry
    Given I login with user "admin"
     Then I get the total hours from "nike-site" project
     Then I delete the latest tracking entry
      And I validate that total hours have "decremented" by "6"
