Feature: Per-issue Table
  In order to be able to access the per-issue table
  As an authenticated user
  We need to be able to see each issue in a project
  Confirm the changes are seen in the table.

  @api
  Scenario: Check the tracking table for a new project.
    Given I am logged in as a user with the "administrator" role
    When  I add a project "Example Project"
    And   I visit per hour table for "Example Project"
    Then  I should see in the "Total" line 0 "Overtime"

  @api
  Scenario: Check tracking table after issue was added.
    Given I am logged in as a user with the "administrator" role
    When  I add issue "Example Issue" for "Example Project"
    And   I visit per hour table for "Example Project"
    Then  I should see in the "Example Issue" line 0 "Overtime"
    And   I should see in the "Total" line 0 "Overtime"

  @api
  Scenario: Check tracking table after tracking for issue was added.
    Given I am logged in as a user with the "administrator" role
    And   I add 1 hour tracking for "Example Issue" in "Example Project"
    And   I visit per hour table for "Example Project"
    Then  I should see in the "Example Issue" line 1 "Overtime"
    And   I should see in the "Total" line 1 "Overtime"

  @api
  Scenario: Check tracking table after another issue was added.
    Given I am logged in as a user with the "administrator" role
    When  I add issue "Example Issue 2" for "Example Project"
    And   I visit per hour table for "Example Project"
    Then  I should see in the "Example Issue 2" line 0 "Overtime"

  @api
  Scenario: Check tracking table after another pull request was added.
    Given I am logged in as a user with the "administrator" role
    When  I add pull request for issue "Example Issue 2" in "Example Project"
    And   I visit per hour table for "Example Project"
    Then  I should see in the "Example Issue 2" line 0 "Overtime"

  @api
  Scenario: Check tracking table after tracking for the pull request was added.
    Given I am logged in as a user with the "administrator" role
    And   I add 1 hour tracking for the pull request for "Example Issue 2" in "Example Project"
    And   I visit per hour table for "Example Project"
    Then  I should see in the "Example Issue 2" line 1 "Overtime"
