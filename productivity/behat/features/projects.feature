Feature: Projects test
  Test Projects page

  @javascript
  Scenario Outline: Test nike site in the projects page and validate that the type is Fix
    Given I login with user "admin"
    When  I visit the "Projects"
    Then  I validate if the type of "<project_name>" project is "<type>"

    Examples:
      | project_name  | type |
      | nike Site     | Fix  |
      | Nike CRM      | Fix  |
      | Nike run fast | T&M  |
