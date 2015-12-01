<?php

use Drupal\DrupalExtension\Context\DrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Behat\Behat\Tester\Exception\PendingException;

class FeatureContext extends DrupalContext implements SnippetAcceptingContext {

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
   * @When /^I open the calendar$/
   */
  public function iOpenTheCalendar() {
    $element = $this->getSession()->getPage();
    $element->pressButton('Show Calendar');
    $this->iShouldWaitForTheTextTo('Log work', 'appear');
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
   * @Given I add one hour tracking for :issue_name in :project_name
   */
  public function iAddHourTrackingForIn($issue_name, $project_name) {
    $this->iCreateNodeOfType('tracking for ' . $issue_name, 'time_tracking', $project_name, $issue_name);
  }

  /**
   * @Given I add one hour tracking for the pull request for :issue_name in :project_name
   */
  public function iAddHourTrackingForThePullRequestForIn($issue_name, $project_name) {
    throw new PendingException();
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
    $entity->title = $title;
    $wrapper = entity_metadata_wrapper('node', $entity);

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

    if ($type == 'time_tracking') {
      // Set relevant fields.
      if ($project_node_id = $this->getNodeIdByTitleBundleAndRef('project', $project_name)) {
        $wrapper->field_project->set($project_node_id);
      }

      $issue_ref = $this->getNodeIdByTitleBundleAndRef('github_issue', $issue_name, $project_node_id);

      $wrapper->field_description->set("foo");
      $wrapper->field_work_date->set(time());
      $wrapper->field_employee->set(1);
      $wrapper->field_day_type->set('regular');
      $wrapper->field_track_hours->set(1);
      $wrapper->field_issues_logs->set(array(
        0 => array(
          'field_github_issue' => array(LANGUAGE_NONE => array(0 => array('target_id' => $issue_ref))),
          'field_issue_label' => array(LANGUAGE_NONE => array(0 => array('value' => 'Example label'))),
          'field_time_spent' => array(LANGUAGE_NONE => array(0 => array('value' => 1))),
          'field_issue_type' => array(LANGUAGE_NONE => array(0 => array('value' => 'dev'))),
        ),
      ));


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
    $wrapper->field_type->set('T&M');
    $wrapper->field_rate_type->set('hours');
    $wrapper->field_github_repository_name->set(array('Example/Example'));

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
}

