<?php

use Drupal\DrupalExtension\Context\DrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Behat\Behat\Tester\Exception\PendingException;

class FeatureContext extends DrupalContext implements SnippetAcceptingContext {

  /**
   *  The total hours of a project.
   */
  protected $total_hours;

  /**
   *  The name of the project being tested.
   */
  protected $project_name;

  /**
   * @When /^I login with user "([^"]*)"$/
   */
  public function iLoginWithUser($name) {
    $password = $name == 'admin' ? 'admin' : '1234';
    $this->loginUser($name, $password);
  }

  /**
   * Login a user to the site.
   *
   * @param $name
   *   The user name.
   * @param $password
   *   The use password.
   */
  protected function loginUser($name, $password) {
    $this->user = new stdClass();
    $this->user->name = $name;
    $this->user->pass = $password;
    $this->login();
  }

  /**
   * @When /^I login with bad credentials$/
   */
  public function iLoginWithBadCredentials() {
    $this->loginUser('wrong-foo', 'wrong-bar');
  }

  /**
   * @When /^I visit the homepage$/
   */
  public function iVisitTheHomepage() {
    $this->getSession()->visit($this->locatePath('/'));
  }

  /**
   * @When /^I visit the "([^"]*)" page$/
   */
  public function iVisitThePage($path) {
    $this->getSession()->visit($this->locatePath($path));
  }

  /**
   * @When /^I visit "([^"]*)" node of type "([^"]*)"$/
   */
  public function iVisitNodePageOfType($title, $type) {
    $query = new \entityFieldQuery();
    $result = $query
      ->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', strtolower($type))
      ->propertyCondition('title', $title)
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyOrderBy('nid', 'DESC')
      ->range(0, 1)
      ->execute();
    if (empty($result['node'])) {
      $params = array(
        '@title' => $title,
        '@type' => $type,
      );
      throw new \Exception(format_string("Node @title of @type not found.", $params));
    }
    $nid = key($result['node']);
    $params['@nid'] = $nid;
    $this->getSession()->visit($this->locatePath('node/' . $nid));
  }


  /**
   * @Then /^I should wait for the text "([^"]*)" to "([^"]*)"$/
   */
  public function iShouldWaitForTheTextTo($text, $appear) {
    $this->waitForXpathNode(".//*[contains(normalize-space(string(text())), \"$text\")]", $appear == 'appear');
  }

  /**
   * @Then /^I wait for css element "([^"]*)" to "([^"]*)"$/
   */
  public function iWaitForCssElement($element, $appear) {
    $xpath = $this->getSession()->getSelectorsHandler()->selectorToXpath('css', $element);
    $this->waitForXpathNode($xpath, $appear == 'appear');
  }
  /**
   * @AfterStep
   *
   * Take a screen shot after failed steps for Selenium drivers (e.g.
   * PhantomJs).
   */
  public function takeScreenshotAfterFailedStep($event) {
    if ($event->getTestResult()->isPassed()) {
      // Not a failed step.
      return;
    }

    if ($this->getSession()->getDriver() instanceof \Behat\Mink\Driver\Selenium2Driver) {
      $file_name = sys_get_temp_dir() . DIRECTORY_SEPARATOR . 'behat-failed-step.png';
      $screenshot = $this->getSession()->getDriver()->getScreenshot();
      file_put_contents($file_name, $screenshot);
      print "Screenshot for failed step created in $file_name";
    }
  }
  /**
   * @BeforeScenario
   *
   * Delete the RESTful tokens before every scenario, so user starts as
   * anonymous.
   */
  public function deleteRestfulTokens($event) {
    if (!module_exists('restful_token_auth')) {
      // Module is disabled.
      return;
    }
    if (!$entities = entity_load('restful_token_auth')) {
      // No tokens found.
      return;
    }
    foreach ($entities as $entity) {
      $entity->delete();
    }
  }

  /**
   * @BeforeScenario
   *
   * Resize the view port.
   */
  public function resizeWindow() {
    if ($this->getSession()->getDriver() instanceof \Behat\Mink\Driver\Selenium2Driver) {
      $this->getSession()->resizeWindow(1440, 900, 'current');
    }
  }

  /**
   * Helper function; Execute a function until it return TRUE or timeouts.
   *
   * @param $fn
   *   A callable to invoke.
   * @param int $timeout
   *   The timeout period. Defaults to 90 seconds.
   *
   * @throws Exception
   */
  private function waitFor($fn, $timeout = 90000) {
    $start = microtime(true);
    $end = $start + $timeout / 1000.0;
    while (microtime(true) < $end) {
      if ($fn($this)) {
        return;
      }
    }
    throw new \Exception('waitFor timed out.');
  }
  /**
   * Wait for an element by its XPath to appear or disappear.
   *
   * @param string $xpath
   *   The XPath string.
   * @param bool $appear
   *   Determine if element should appear. Defaults to TRUE.
   *
   * @throws Exception
   */
  private function waitForXpathNode($xpath, $appear = TRUE) {
    $this->waitFor(function($context) use ($xpath, $appear) {
        try {
          $nodes = $context->getSession()->getDriver()->find($xpath);
          if (count($nodes) > 0) {
            $visible = $nodes[0]->isVisible();
            return $appear ? $visible : !$visible;
          }
          return !$appear;
        }
        catch (WebDriver\Exception $e) {
          if ($e->getCode() == WebDriver\Exception::NO_SUCH_ELEMENT) {
            return !$appear;
          }
          throw $e;
        }
      });
  }

  /**
   * @Given /^I wait$/
   */
  public function iWait() {
    sleep(10);
  }

  /**
   * @When I add a project named :project_name
   */
  public function iAddAProjectNamed($project_name) {
    $this->iCreateNodeOfType($project_name, 'project', NULL);
  }

  /**
   * @When I visit per issue table for :project_name
   */
  public function iVisitPerIssueTableFor($project_name) {
    $project_node_id = $this->getNodeIdByTitleBundleAndRef('project', $project_name);
    $this->getSession()->visit($this->locatePath('tracking/per-issue/' . $project_node_id));
  }

  /**
   * @Then I should see in the :line_name line :value :column
   */
  public function iShouldSeeInTheLine($line_name, $column, $value) {
    // List of columns and their nth-child values.
    $columns = array(
      'Issue ID' => 1,
      'Issue name' => 2,
      'Time estimate' => 3,
      'Actual time' => 4,
      'Overtime' => 5,
      'Status' => 6,
    );
    $column_number = $columns[$column];

    // Get table rows.
    $page = $this->getSession()->getPage();
    $elements = $page->findAll('css', ".per-issue-table tr");
    if (empty($elements)) {
      throw new \Exception("Per issue table not found.");
    }

    // Remove the header row.
    unset($elements[0]);

    // Find correct row.
    foreach($elements as $element) {
      $name  = $element->find('css', ':nth-child(2)')->getText();

      if ($name == $line_name) {
        $column_value = $element->find('css', ':nth-child(' . $column_number . ')')->getText();
        if ($column_value != $value) {
          throw new \Exception('Wrong value when checking the per-issue table.');
        }
        break;
      }
    }
  }

  /**
   * @When I add issue :issue_name for :project_name
   */
  public function iAddIssueFor($issue_name, $project_name) {
    $this->iCreateNodeOfType($issue_name, 'github_issue', $project_name);
  }

  /**
   * @When I add pull request for issue :issue_name in :project_name
   */
  public function iAddPullRequestForIssueFor($issue_name, $project_name) {
    $pull_reuqest_name = 'Example pull request for' . $issue_name;
    $this->iCreateNodeOfType($pull_reuqest_name, 'github_issue', $project_name, $issue_name);
  }

  /**
   * @When I create :title node of type :type
   */
  public function iCreateNodeOfType($title, $type, $project_name = NULL, $issue_name = NULL, $check_saving = FALSE) {
    $account = user_load_by_name($this->user->name);
    $values = array(
      'type' => $type,
      'uid' => $account->uid,
    );

    $entity = entity_create('node', $values);
    $wrapper = entity_metadata_wrapper('node', $entity);
    $wrapper->title->set($title);

    if ($type == 'project') {
      $wrapper->field_scope->set(array(
        'interval' => 10,
        'period' => 'month',
      ));
    }

    if ($type == 'github_issue') {
      // Set some more fields if available.
      if ($project_node_id = $this->getNodeIdByTitleBundleAndRef('project', $project_name)) {
        $wrapper->field_project->set($project_node_id);
        $wrapper->field_github_content_type->set('issue');
        $wrapper->field_issue_id->set(12);

        if ($issue_name) {
          $issue_ref = $this->getNodeIdByTitleBundleAndRef('github_issue', $issue_name, $project_node_id);
          $wrapper->field_issue_reference->set($issue_ref);
          $wrapper->field_github_content_type->set('pull_request');
        }
      }
    }

    try {
      $wrapper->save();

      return TRUE;
    }
    catch (\Exception $e) {
      if (!$check_saving) {
        throw $e;
      }
      return FALSE;
    }
  }

  /**
   * @When I create a project named :title
   */
  public function iCreateAProjectNamed($title, $check_saving = FALSE) {
    $account = user_load_by_name($this->user->name);
    $values = array(
      'title' => $title,
      'type' => 'project',
      'uid' => $account->uid,
    );

    $entity = entity_create('node', $values);
//    $entity->title = $title;
    $wrapper = entity_metadata_wrapper('node', $entity);

    // Some default values.
    // TODO: fix using new filed collection
//    $wrapper->field_type->set('T&M');
//    $wrapper->field_rate_type->set('hours');
//    $wrapper->field_github_repository_name->set(array('Example/Example'));

    try {
      $wrapper->save();
      return TRUE;
    }
    catch (\Exception $e) {
      if (!$check_saving) {
        throw $e;
      }
      return FALSE;
    }
  }


  /**
   * Get node ID by bundle and title.
   *
   * @param string $bundle
   *    The name of bundle (type) of node searching for.
   * @param string $title
   *    The title of node searching for.
   * @param $project_ref int (optional)
   *    The node ID of the project referenced.
   * @param $issue_ref int (optional)
   *    The node ID of the issue referenced.
   *
   * @return int
   *    The Node ID.
   *
   * @throws \Exception
   *    The error if node not found.
   */
  public function getNodeIdByTitleBundleAndRef($bundle, $title, $project_ref = NULL, $issue_ref = NULL) {
    $bundle = str_replace(array(' ', '-'), '_', $bundle);
    $query = new \entityFieldQuery();
    $query
      ->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', strtolower($bundle))
      ->propertyCondition('title', $title)
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyOrderBy('nid', 'DESC')
      ->range(0, 1);

    if ($project_ref) {
      $query->fieldCondition('field_project','target_id', $project_ref);

      if ($issue_ref) {
        $query->fieldCondition('field_issue_reference', 'target_id', $issue_ref);
      }
    }
    $result = $query->execute();

    if (empty($result['node'])) {
      $params = array(
        '@title' => $title,
        '@type' => $bundle,
      );
      throw new \Exception(format_string("Node @title of @type not found.", $params));
    }
    $nid = key($result['node']);
    return $nid;
  }


  /**
   * @Then The response status code should be :code
   */
  public function theResponseStatusCodeShouldBe($code) {
    $session = $this->getSession();

    $response_code = $session->getStatusCode();
    if ($response_code != $code)  {
      $params['@code'] = $response_code;
      throw new \Exception(format_string("Wrong status code, @code", $params));
    }
  }

  /**
   * Get total hours in a project.
   *
   * @param $project_name
   *  The name of the project.
   *
   * @return int
   *  The total hours in the project.
   * @throws \Exception
   */
  public function getTotalHours($project_name) {
    $this->getSession()->visit($this->locatePath('content/' . $project_name));
    $page = $this->getSession()->getPage();

    if (!$element = $page->find('xpath', '//div[@class="field-item even"]')) {
      throw new \Exception('The element was not found in the page.');
    }

    $total_hours_text = $element->getText();

    // Removing whitespace in case $total_hoursText >= 1 000
    $total_hours = intval(str_replace(' ', '', $total_hours_text));

    return $total_hours;
  }

  /**
   * @Given /^I get the total hours from "([^"]*)" project$/
   */
  public function iGetTheTotalHours($project_name) {
    $this->project_name = $project_name;
    $total_hours = $this->getTotalHours($project_name);

    $this->total_hours = $total_hours;
  }

  /**
   * @Given /^I validate that total hours have "([^"]*)" by "([^"]*)"$/
   */
  public function iValidateTheTotalHours($type, $hours) {
    $new_total_hours = $this->getTotalHours($this->project_name);
    switch ($type) {
      case "incremented":
        $expected_sum = $this->total_hours + $hours;
        break;

      case "decremented":
        $expected_sum = $this->total_hours - $hours;
        print("\nOriginal Hours: " . $this->total_hours);
        print("\nDecremented Hours: " . $hours);
        print("\nExpected Sum: " . $expected_sum);
        break;

      default:
        throw new Exception('Wrong arithmetic type provided.');
    }

    print("\nTotal Hours: ". $new_total_hours . " Expected Sum: " . $expected_sum );
    if ($new_total_hours != $expected_sum ) {
      throw new Exception("The total hours didn't match the expected number.");
    }
  }

  /**
   * @Then /^I add a new time tracking to the issue "([^"]*)" with "([^"]*)" hours to "([^"]*)" project$/
   */
  public function iAddANewTimeTrackingEntry($issue, $hours, $project) {
    $this->getSession()->visit($this->locatePath('node/add/time-tracking'));
    $element = $this->getSession()->getPage();

    $element->fillField('Title', 'Not relevant');
    $element->selectFieldOption('Project', $project);
    $element->selectFieldOption('Employee', $this->user->name);
    $element->fillField('edit-field-description-und-0-value', 'Example description');
    $this->fillInDrupalAutocomplete('GitHub issue', $issue, $issue);

    $element->fillField('Time Spent', $hours);
    $element->selectFieldOption('Issue type', 'Development');
    $element->find('css', '#edit-submit')->click();

    // This must be called to save the entity one more time to take effect on
    // the project report.
    $this->iAddHoursToLatestTrackingEntry(0);
  }

  /**
   * Get latest time-tracking entity.
   *
   * @return mixed|void
   *  The latest time-tracking node ID | FALSE.
   */
  function getLatestTrackingEntry() {
    $query = new EntityFieldQuery();
    $result = $query
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('type', 'time_tracking')
      ->propertyOrderBy('created', 'DESC')
      ->range(0, 1)
      ->execute();

    if (empty($result['node'])) {
      return FALSE;
    }
    return key($result['node']);
  }

  /**
   * @Then /^I add "([^"]*)" hours to the latest tracking entry$/
   */
  public function iAddHoursToLatestTrackingEntry($hours) {
    $entity_id = $this->getLatestTrackingEntry();
    $this->getSession()->visit($this->locatePath("node/$entity_id/edit"));
    $element = $this->getSession()->getPage();

    $time_spent_el = $element->find('css', '#edit-field-issues-logs-und-0-field-time-spent-und-0-value');
    $time_spent = $time_spent_el->getValue();

    if ( isset($time_spent) ) {
      $hours += $time_spent;
    }

    $element->fillField('Time Spent', $hours);
    $element->find('css', '#edit-submit')->click();
  }

  /**
   * @Then /^I delete the latest tracking entry$/
   */
  public function iDeleteLatestTrackingEntry() {
    $entity_id = $this->getLatestTrackingEntry();
    $this->getSession()->visit($this->locatePath("node/$entity_id/delete"));
    $element = $this->getSession()->getPage();
    $element->find('css', '#edit-submit')->click();
  }

  /**
   * Select a value from entity-reference auto-complete field.
   *
   * @param $autocomplete
   *  The name of the auto-complete field.
   * @param $text
   *  The text to add to the field.
   * @param $popup
   *  The text of the pop-up
   *
   * @throws \ExpectationException
   */
  protected function fillInDrupalAutocomplete($autocomplete, $text, $popup) {
    $el = $this->getSession()->getPage()->findField($autocomplete);
    $el->focus();

    // Set the autocomplete text then put a space at the end which triggers
    // the JS to go do the autocomplete stuff.
    $el->setValue($text);
    $el->keyUp(' ');

    // Sadly this grace of 1 second is needed here.
    sleep(1);

    // Drupal autocompletes have an id of autocomplete which is bad news
    // if there are two on the page.
    $autocomplete = $this->getSession()->getPage()->findById('autocomplete');

    if (empty($autocomplete)) {
      throw new ExpectationException(t('Could not find the autocomplete popup box'), $this->getSession());
    }

    $popup_element = $autocomplete->find('xpath', "//div[text() = '{$popup}']");

    if (empty($popup_element)) {
      throw new ExpectationException(t('Could not find autocomplete popup text @popup', array(
        '@popup' => $popup)), $this->getSession());
    }

    $popup_element->click();
  }
}

