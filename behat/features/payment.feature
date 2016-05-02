Feature: Check if a payment exists
  Check for a specific unpaid payment

  @javascript @wip
  Scenario Outline: Check for an upaid payment
    Given I login the user "admin"
    When I navigate to the payments page
    When I click on the "<payment>" payment
    Then I should check for missing data in
      | nike Site | $2,000.00 | Monday, 2 June, 2014    |
      | nike Site | $2,500.00 | Thursday, 3 July, 2014  |
      | nike Site | $1,100.00 | Sunday, 10 August, 2014 |

    Examples:
      | payment| project   | amount    | date                    |
      | Second | nike Site | $2,000.00 | Monday, 2 June, 2014    |
      | Third  | nike Site | $2,500.00 | Thursday, 3 July, 2014  |
      |  Last  | nike Site | $1,100.00 | Sunday, 10 August, 2014 |