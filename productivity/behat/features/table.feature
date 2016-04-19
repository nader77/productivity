Feature: Per-issue Table
  In order to be able to access the per-issue table
  As an authenticated user
  We need to be able to see each issue in a project
  Confirm the changes are seen in the table.

  @api
  Scenario: Check the tracking table for a new project.
    Given I login with user "admin"
    When  I add a project named "Example Project"
    And   I visit per issue table for "Example Project"
    Then  I should see the text "No issues found for project Example Project"

  @api
  Scenario: Check tracking table after issue was added.
    Given I login with user "admin"
    When  I add issue "Example Issue" for "Example Project"
    And   I visit per issue table for "Example Project"
    Then  I should see in the "Example Issue" line 0 "Overtime"
    And   I should see in the "Total" line 0 "Overtime"

  @javascript
  Scenario: Check tracking table after tracking for issue was added.
    Given I login with user "admin"
    When  I add a new time tracking to the issue "Example Issue" with "1" hours to "Example Project" project
    And   I visit per issue table for "Example Project"
    Then  I should see in the "Example Issue" line 1 "Overtime"
    And   I should see in the "Total" line 1 "Overtime"

  @api
  Scenario: Check tracking table after another issue was added.
    Given I login with user "admin"
    When  I add issue "Example Issue 2" for "Example Project"
    And   I visit per issue table for "Example Project"
    Then  I should see in the "Example Issue 2" line 0 "Overtime"

  @api
  Scenario: Check tracking table after another pull request was added.
    Given I login with user "admin"
    When  I add pull request for issue "Example Issue 2" in "Example Project"
    And   I visit per issue table for "Example Project"
    Then  I should see in the "Example Issue 2" line 0 "Overtime"

  @javascript
  Scenario: Check tracking table after tracking for the pull request was added.
    Given I login with user "admin"
    When  I add a new time tracking to the issue "Example Issue 2" with "1" hours to "Example Project" project
    And   I visit per issue table for "Example Project"
    Then  I should see in the "Example Issue 2" line 1 "Overtime"
