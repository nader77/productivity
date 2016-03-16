Feature: Time tracking
  When add or editing or deleting tracking, I should see
  the total tracking on the project page is updated accordingly

  @api
  Scenario: Adding a new tracking entry
    Given I login with user "avi"
     Then I get the total hours from "nike-site" project
     Then I add a new time tracking entry with "3" hours
      And I validate that total hours have incremented by "3"

  Scenario: Editing an existing tracking entry
    Given I login with user "avi"
     Then I get the total hours from "nike-site" project
     Then I add "3" hours to the lastest tracking entry
      And I validate that total hours have incremented by "3"
