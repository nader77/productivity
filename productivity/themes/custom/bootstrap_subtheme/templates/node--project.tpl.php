<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>
<?php dpm($content); ?>
<div class="row">
  <div class="col-lg-3 col-sm-6 col-xs-12">
    <div class="main-box infographic-box">
      <i class="fa fa-hand-o-up red-bg"></i>
      <span class="headline">Total Hours</span>
      <span class="value"><?php print render($content['field_hours']);?></span>
    </div>
    <div class="main-box infographic-box">
      <i class="fa fa-money yellow-bg"></i>
      <span class="headline">Total Scope</span>
      <span class="value"><?php print render($content['field_scope']);?></span>
    </div>
  </div>
<!--
field_scope
field_account
field_date
field_type
field_rate_type
field_rate
field_status
field_github_repository_name
field_days
-->
  <div class="col-lg-3 col-sm-6 col-xs-12">
    <div class="main-box infographic-box">
      <i class="fa fa-shopping-cart emerald-bg"></i>
      <span class="headline">Type</span>
      <span class="value"><?php print render($content['field_type']);?></span>
    </div>
  </div>
  <div class="col-lg-3 col-sm-6 col-xs-12">
    <div class="main-box infographic-box">
      <i class="fa fa-money green-bg"></i>
      <span class="headline">Rate</span>
      <span class="value"><?php print render($content['field_rate']);?></span>
    </div>
  </div>
  <div class="col-lg-3 col-sm-6 col-xs-12">
    <div class="main-box infographic-box">
      <i class="fa fa-money yellow-bg"></i>
      <span class="headline">Days</span>
      <span class="value"><?php print render($content['field_days']);?></span>
    </div>
  </div>
</div

  <?php print render($content['links']); ?>
  <?php print render($content);?>
  <?php if (node_access('update', $node)) : ?>
    <a href="<?php print url('recalculate-project-time/' . $node->nid) ?>"><?php print t('Recalculate project\'s hours & days.') ?></a>
  <?php endif; ?>

<div id="theme-wrapper">
  <div id="page-wrapper" class="container">
    <div class="row">
      <div id="content-wrapper">
        <div class="row">
          <div class="col-lg-12">

            <div class="row">
              <div class="col-lg-12">
                <ol class="breadcrumb">
                  <li><a href="#">Home</a></li>
                  <li class="active"><span>Widgets</span></li>
                </ol>

                <h1>Widgets</h1>
              </div>
            </div>

            <div class="row">
              <div class="col-lg-5 col-md-8 col-sm-12 col-xs-12">
                <div class="main-box">
                  <div class="clearfix">
                    <div class="infographic-box merged merged-top pull-left">
                      <i class="fa fa-user purple-bg"></i>
                      <span class="value purple">2.562</span>
                      <span class="headline">Users</span>
                    </div>
                    <div class="infographic-box merged merged-top merged-right pull-left">
                      <i class="fa fa-money green-bg"></i>
                      <span class="value green">&dollar;12.400</span>
                      <span class="headline">Income</span>
                    </div>
                  </div>
                  <div class="clearfix">
                    <div class="infographic-box merged pull-left">
                      <i class="fa fa-eye yellow-bg"></i>
                      <span class="value yellow">12.526</span>
                      <span class="headline">Monthly Visits</span>
                    </div>
                    <div class="infographic-box merged merged-right pull-left">
                      <i class="fa fa-globe red-bg"></i>
                      <span class="value red">28</span>
                      <span class="headline">Countries</span>
                    </div>
                  </div>
                </div>
              </div>

              <div class="col-md-4 col-sm-6 col-xs-12">
                <div class="main-box small-graph-box red-bg">
                  <span class="value">2.562</span>
                  <span class="headline">Users</span>
                  <div class="progress">
                    <div style="width: 60%;" aria-valuemax="100" aria-valuemin="0" aria-valuenow="60" role="progressbar" class="progress-bar">
                      <span class="sr-only">60% Complete</span>
                    </div>
                  </div>
										<span class="subinfo">
											<i class="fa fa-arrow-circle-o-up"></i> 10% higher than last week
										</span>
										<span class="subinfo">
											<i class="fa fa-users"></i> 29 new users
										</span>
                </div>
              </div>

              <div class="col-lg-3 col-sm-6 col-xs-12">
                <div class="main-box infographic-box">
                  <i class="fa fa-shopping-cart emerald-bg"></i>
                  <span class="headline">Purchases</span>
                  <span class="value">658</span>
                </div>
              </div>

            </div>

            <div class="row">
              <div class="col-md-9 col-lg-10">
                <div class="main-box">
                  <div class="row">
                    <div class="col-md-9">
                      <div class="graph-box emerald-bg">
                        <h2>Sales &amp; Earnings</h2>
                        <div class="graph" id="graph-line" style="max-height: 335px;"></div>
                      </div>
                    </div>
                    <div class="col-md-3">
                      <div class="row graph-nice-legend">
                        <div class="graph-legend-row col-md-12 col-sm-4">
                          <div class="graph-legend-row-inner">
															<span class="graph-legend-name">
																Earnings
															</span>
															<span class="graph-legend-value">
																&dollar;94.382
															</span>
                          </div>
                        </div>
                        <div class="graph-legend-row col-md-12 col-sm-4">
                          <div class="graph-legend-row-inner">
															<span class="graph-legend-name">
																Orders
															</span>
															<span class="graph-legend-value">
																3.930
															</span>
                          </div>
                        </div>
                        <div class="graph-legend-row col-md-12 col-sm-4">
                          <div class="graph-legend-row-inner">
															<span class="graph-legend-name">
																New Clients
															</span>
															<span class="graph-legend-value">
																894
															</span>
                          </div>
                        </div>
                      </div>
                    </div>
                  </div>
                </div>
              </div>

              <div class="col-md-3 col-lg-2">
                <div class="social-box-wrapper">
                  <div class="social-box col-md-12 col-sm-4 facebook">
                    <i class="fa fa-facebook"></i>
                    <div class="clearfix">
                      <span class="social-count">184k</span>
                      <span class="social-action">likes</span>
                    </div>
                    <span class="social-name">facebook</span>
                  </div>
                  <div class="social-box col-md-12 col-sm-4 twitter">
                    <i class="fa fa-twitter"></i>
                    <div class="clearfix">
                      <span class="social-count">49k</span>
                      <span class="social-action">tweets</span>
                    </div>
                    <span class="social-name">twitter</span>
                  </div>
                  <div class="social-box col-md-12 col-sm-4 google">
                    <i class="fa fa-google-plus"></i>
                    <div class="clearfix">
                      <span class="social-count">1 204</span>
                      <span class="social-action">circles</span>
                    </div>
                    <span class="social-name">google+</span>
                  </div>
                </div>
              </div>
            </div>

            <div class="row">
              <div class="col-lg-4 col-md-5 col-sm-6">
                <div class="main-box clearfix profile-box">
                  <div class="main-box-body clearfix">
                    <div class="profile-box-header">
                      <img src="img/samples/scarlet-159.png" alt="" class="profile-img img-responsive center-block" />
                      <h2>Scarlett Johansson</h2>
                      <div class="job-position">
                        Actress
                      </div>
                    </div>

                    <div class="profile-box-footer clearfix">
                      <a href="#">
                        <span class="value">854</span>
                        <span class="label">Followers</span>
                      </a>
                      <a href="#">
                        <span class="value">72</span>
                        <span class="label">Following</span>
                      </a>
                      <a href="#">
                        <span class="value">128</span>
                        <span class="label">Friends</span>
                      </a>
                    </div>
                  </div>
                </div>
              </div>

              <div class="col-lg-4 col-md-5 col-sm-6">
                <div class="main-box clearfix profile-box-stats">
                  <div class="main-box-body clearfix">
                    <div class="profile-box-header purple-bg clearfix">
                      <h2>Robert Downey Jr.</h2>
                      <div class="job-position">
                        Actress
                      </div>
                      <img src="img/samples/robert-300.jpg" alt="" class="profile-img img-responsive" />
                    </div>

                    <div class="profile-box-footer clearfix">
                      <a href="#">
                        <span class="value">783</span>
                        <span class="label">Messages</span>
                      </a>
                      <a href="#">
                        <span class="value">912</span>
                        <span class="label">Sales</span>
                      </a>
                      <a href="#">
                        <span class="value">83</span>
                        <span class="label">Projects</span>
                      </a>
                    </div>
                  </div>
                </div>
              </div>

              <div class="col-lg-4 col-md-5 col-sm-6">
                <div class="main-box clearfix profile-box-menu">
                  <div class="main-box-body clearfix">
                    <div class="profile-box-header green-bg clearfix">
                      <img src="img/samples/angelina-300.jpg" alt="" class="profile-img img-responsive" />
                      <h2>Angelina<br/>Jolie</h2>
                      <div class="job-position">
                        Actress
                      </div>
                    </div>

                    <div class="profile-box-content clearfix">
                      <ul class="menu-items">
                        <li>
                          <a href="#" class="clearfix">
                            <i class="fa fa-bell-o fa-lg"></i> New notifications
                            <span class="label label-danger label-circle pull-right">82</span>
                          </a>
                        </li>
                        <li>
                          <a href="#" class="clearfix">
                            <i class="fa fa-user fa-lg"></i> Edit profile
                            <span class="label label-success label-circle pull-right">13</span>
                          </a>
                        </li>
                        <li>
                          <a href="#" class="clearfix">
                            <i class="fa fa-calendar fa-lg"></i> Calendar
                            <span class="label label-warning label-circle pull-right">12</span>
                          </a>
                        </li>
                        <li>
                          <a href="#" class="clearfix">
                            <i class="fa fa-envelope fa-lg"></i> New message
                            <span class="label label-primary label-circle pull-right">44</span>
                          </a>
                        </li>
                      </ul>
                    </div>
                  </div>
                </div>
              </div>

            </div>

            <div class="row">
              <div class="col-lg-6">
                <div class="main-box clearfix">
                  <header class="main-box-header clearfix">
                    <h2>Conversation</h2>
                  </header>

                  <div class="main-box-body clearfix">
                    <div class="conversation-wrapper">
                      <div class="conversation-content">
                        <div class="conversation-inner">

                          <div class="conversation-item item-left clearfix">
                            <div class="conversation-user">
                              <img src="img/samples/ryan.png" alt=""/>
                            </div>
                            <div class="conversation-body">
                              <div class="name">
                                Ryan Gossling
                              </div>
                              <div class="time hidden-xs">
                                September 21, 2013 18:28
                              </div>
                              <div class="text">
                                I don't think they tried to market it to the billionaire, spelunking,
                                base-jumping crowd.
                              </div>
                            </div>
                          </div>
                          <div class="conversation-item item-right clearfix">
                            <div class="conversation-user">
                              <img src="img/samples/kunis.png" alt=""/>
                            </div>
                            <div class="conversation-body">
                              <div class="name">
                                Mila Kunis
                              </div>
                              <div class="time hidden-xs">
                                September 21, 2013 12:45
                              </div>
                              <div class="text">
                                The path of the righteous man is beset on all sides by the iniquities of the
                                selfish and the tyranny of evil men. Blessed is he who, in the name of charity and
                                good will.
                              </div>
                            </div>
                          </div>
                          <div class="conversation-item item-right clearfix">
                            <div class="conversation-user">
                              <img src="img/samples/kunis.png" alt=""/>
                            </div>
                            <div class="conversation-body">
                              <div class="name">
                                Mila Kunis
                              </div>
                              <div class="time hidden-xs">
                                September 21, 2013 12:45
                              </div>
                              <div class="text">
                                The path of the righteous man is beset on all sides by the iniquities of the
                                selfish and the tyranny of evil men. Blessed is he who, in the name of charity and
                                good will.
                              </div>
                            </div>
                          </div>
                          <div class="conversation-item item-left clearfix">
                            <div class="conversation-user">
                              <img src="img/samples/ryan.png" alt=""/>
                            </div>
                            <div class="conversation-body">
                              <div class="name">
                                Ryan Gossling
                              </div>
                              <div class="time hidden-xs">
                                September 21, 2013 18:28
                              </div>
                              <div class="text">
                                I don't think they tried to market it to the billionaire, spelunking,
                                base-jumping crowd.
                              </div>
                            </div>
                          </div>
                          <div class="conversation-item item-right clearfix">
                            <div class="conversation-user">
                              <img src="img/samples/kunis.png" alt=""/>
                            </div>
                            <div class="conversation-body">
                              <div class="name">
                                Mila Kunis
                              </div>
                              <div class="time hidden-xs">
                                September 21, 2013 12:45
                              </div>
                              <div class="text">
                                The path of the righteous man is beset on all sides by the iniquities of the
                                selfish and the tyranny of evil men. Blessed is he who, in the name of charity and
                                good will.
                              </div>
                            </div>
                          </div>
                          <div class="conversation-item item-right clearfix">
                            <div class="conversation-user">
                              <img src="img/samples/kunis.png" alt=""/>
                            </div>
                            <div class="conversation-body">
                              <div class="name">
                                Mila Kunis
                              </div>
                              <div class="time hidden-xs">
                                September 21, 2013 12:45
                              </div>
                              <div class="text">
                                The path of the righteous man is beset on all sides by the iniquities of the
                                selfish and the tyranny of evil men. Blessed is he who, in the name of charity and
                                good will.
                              </div>
                            </div>
                          </div>
                          <div class="conversation-item item-left clearfix">
                            <div class="conversation-user">
                              <img src="img/samples/ryan.png" alt=""/>
                            </div>
                            <div class="conversation-body">
                              <div class="name">
                                Ryan Gossling
                              </div>
                              <div class="time hidden-xs">
                                September 21, 2013 18:28
                              </div>
                              <div class="text">
                                I don't think they tried to market it to the billionaire, spelunking,
                                base-jumping crowd.
                              </div>
                            </div>
                          </div>
                          <div class="conversation-item item-right clearfix">
                            <div class="conversation-user">
                              <img src="img/samples/kunis.png" alt=""/>
                            </div>
                            <div class="conversation-body">
                              <div class="name">
                                Mila Kunis
                              </div>
                              <div class="time hidden-xs">
                                September 21, 2013 12:45
                              </div>
                              <div class="text">
                                The path of the righteous man is beset on all sides by the iniquities of the
                                selfish and the tyranny of evil men. Blessed is he who, in the name of charity and
                                good will.
                              </div>
                            </div>
                          </div>

                        </div>
                      </div>
                      <div class="conversation-new-message">
                        <form>
                          <div class="form-group">
                            <textarea class="form-control" rows="2" placeholder="Enter your message..."></textarea>
                          </div>

                          <div class="clearfix">
                            <button type="submit" class="btn btn-success pull-right">Send message</button>
                          </div>
                        </form>
                      </div>
                    </div>
                  </div>
                </div>
              </div>

              <div class="col-lg-6">
                <div class="main-box clearfix">
                  <header class="main-box-header clearfix">
                    <h2>Users</h2>
                  </header>

                  <div class="main-box-body clearfix">

                    <ul class="widget-users row">
                      <li class="col-md-6">
                        <div class="img">
                          <img src="img/samples/scarlet.png" alt=""/>
                        </div>
                        <div class="details">
                          <div class="name">
                            <a href="#">Scarlett Johansson</a>
                          </div>
                          <div class="time">
                            <i class="fa fa-clock-o"></i> Last online: 5 minutes ago
                          </div>
                          <div class="type">
                            <span class="label label-danger">Admin</span>
                          </div>
                        </div>
                      </li>
                      <li class="col-md-6">
                        <div class="img">
                          <img src="img/samples/kunis.png" alt=""/>
                        </div>
                        <div class="details">
                          <div class="name">
                            <a href="#">Mila Kunis</a>
                          </div>
                          <div class="time online">
                            <i class="fa fa-check-circle"></i> Online
                          </div>
                          <div class="type">
                            <span class="label label-warning">Pending</span>
                          </div>
                        </div>
                      </li>
                      <li class="col-md-6">
                        <div class="img">
                          <img src="img/samples/ryan.png" alt=""/>
                        </div>
                        <div class="details">
                          <div class="name">
                            <a href="#">Ryan Gossling</a>
                          </div>
                          <div class="time online">
                            <i class="fa fa-check-circle"></i> Online
                          </div>
                        </div>
                      </li>
                      <li class="col-md-6">
                        <div class="img">
                          <img src="img/samples/robert.png" alt=""/>
                        </div>
                        <div class="details">
                          <div class="name">
                            <a href="#">Robert Downey Jr.</a>
                          </div>
                          <div class="time">
                            <i class="fa fa-clock-o"></i> Last online: Thursday
                          </div>
                        </div>
                      </li>
                      <li class="col-md-6">
                        <div class="img">
                          <img src="img/samples/emma.png" alt=""/>
                        </div>
                        <div class="details">
                          <div class="name">
                            <a href="#">Emma Watson</a>
                          </div>
                          <div class="time">
                            <i class="fa fa-clock-o"></i> Last online: 1 week ago
                          </div>
                        </div>
                      </li>
                      <li class="col-md-6">
                        <div class="img">
                          <img src="img/samples/george.png" alt=""/>
                        </div>
                        <div class="details">
                          <div class="name">
                            <a href="#">George Clooney</a>
                          </div>
                          <div class="time">
                            <i class="fa fa-clock-o"></i> Last online: 1 month ago
                          </div>
                        </div>
                      </li>
                      <li class="col-md-6">
                        <div class="img">
                          <img src="img/samples/kunis.png" alt=""/>
                        </div>
                        <div class="details">
                          <div class="name">
                            <a href="#">Mila Kunis</a>
                          </div>
                          <div class="time online">
                            <i class="fa fa-check-circle"></i> Online
                          </div>
                          <div class="type">
                            <span class="label label-warning">Pending</span>
                          </div>
                        </div>
                      </li>
                      <li class="col-md-6">
                        <div class="img">
                          <img src="img/samples/ryan.png" alt=""/>
                        </div>
                        <div class="details">
                          <div class="name">
                            <a href="#">Ryan Gossling</a>
                          </div>
                          <div class="time online">
                            <i class="fa fa-check-circle"></i> Online
                          </div>
                        </div>
                      </li>
                    </ul>

                  </div>
                </div>
              </div>

            </div>
            <div class="row">

              <div class="col-lg-6">
                <div class="main-box clearfix">
                  <header class="main-box-header clearfix">
                    <h2>Products</h2>
                  </header>

                  <div class="main-box-body clearfix">
                    <ul class="widget-products">
                      <li>
                        <a href="#">
														<span class="img">
															<img src="img/samples/ipad.png" alt=""/>
														</span>

														<span class="product clearfix">
															<span class="name">
																iPad mini 32GB WiFi Black&Slate
															</span>
															<span class="price">
																<i class="fa fa-money"></i> &dollar;320,00
															</span>
															<span class="warranty">
																<i class="fa fa-certificate"></i> Warranty: 2 years
															</span>
														</span>
                        </a>
                      </li>
                      <li>
                        <a href="#">
														<span class="img">
															<img src="img/samples/ipad.png" alt=""/>
														</span>

														<span class="product clearfix">
															<span class="name">
																iPad mini 16GB WiFi Black&Slate
															</span>
															<span class="price">
																<i class="fa fa-money"></i> &dollar;273,68
															</span>
															<span class="warranty">
																<i class="fa fa-certificate"></i> Warranty: 2 years
															</span>
														</span>
                        </a>
                      </li>
                      <li>
                        <a href="#">
														<span class="img">
															<img src="img/samples/ipad.png" alt=""/>
														</span>

														<span class="product clearfix">
															<span class="name">
																iPad mini 32GB WiFi Cellular Black&Slate
															</span>
															<span class="price">
																<i class="fa fa-money"></i> &dollar;447,29
															</span>
															<span class="warranty">
																<i class="fa fa-certificate"></i> Warranty: 4 years
															</span>
														</span>
                        </a>
                      </li>
                      <li>
                        <a href="#">
														<span class="img">
															<img src="img/samples/ipad.png" alt=""/>
														</span>

														<span class="product clearfix">
															<span class="name">
																iPad mini 32GB WiFi Cellular Black&Slate
															</span>
															<span class="price">
																<i class="fa fa-money"></i> &dollar;447,29
															</span>
															<span class="warranty">
																<i class="fa fa-certificate"></i> Warranty: 4 years
															</span>
														</span>
                        </a>
                      </li>
                    </ul>

                  </div>
                </div>
              </div>

              <div class="col-lg-6">
                <div class="main-box clearfix">
                  <header class="main-box-header clearfix">
                    <h2>Todo</h2>
                  </header>

                  <div class="main-box-body clearfix">

                    <ul class="widget-todo">
                      <li class="clearfix">
                        <div class="name">
                          <div class="checkbox-nice">
                            <input type="checkbox" id="todo-1" />
                            <label for="todo-1">
                              New products introduction <span class="label label-danger">High Priority</span>
                            </label>
                          </div>
                        </div>
                      </li>
                      <li class="clearfix">
                        <div class="name">
                          <div class="checkbox-nice">
                            <input type="checkbox" id="todo-2" />
                            <label for="todo-2">
                              Checking the stock <span class="label label-success">Low Priority</span>
                            </label>
                          </div>
                        </div>
                        <div class="actions">
                          <a href="#" class="table-link">
                            <i class="fa fa-pencil"></i>
                          </a>
                          <a href="#" class="table-link danger">
                            <i class="fa fa-trash-o"></i>
                          </a>
                        </div>
                      </li>
                      <li class="clearfix">
                        <div class="name">
                          <div class="checkbox-nice">
                            <input type="checkbox" id="todo-3" checked="checked" />
                            <label for="todo-3">
                              Buying coffee <span class="label label-warning">Medium Priority</span>
                            </label>
                          </div>
                        </div>
                        <div class="actions">
                          <a href="#" class="table-link">
                            <i class="fa fa-pencil"></i>
                          </a>
                          <a href="#" class="table-link danger">
                            <i class="fa fa-trash-o"></i>
                          </a>
                        </div>
                      </li>
                      <li class="clearfix">
                        <div class="name">
                          <div class="checkbox-nice">
                            <input type="checkbox" id="todo-4" />
                            <label for="todo-4">
                              New marketing campaign <span class="label label-success">Low Priority</span>
                            </label>
                          </div>
                        </div>
                      </li>
                      <li class="clearfix">
                        <div class="name">
                          <div class="checkbox-nice">
                            <input type="checkbox" id="todo-5" />
                            <label for="todo-5">
                              Calling Mom <span class="label label-warning">Medium Priority</span>
                            </label>
                          </div>
                        </div>
                        <div class="actions">
                          <a href="#" class="table-link badge">
                            <i class="fa fa-cog"></i>
                          </a>
                        </div>
                      </li>
                      <li class="clearfix">
                        <div class="name">
                          <div class="checkbox-nice">
                            <input type="checkbox" id="todo-6" />
                            <label for="todo-6">
                              Ryan's birthday <span class="label label-danger">High Priority</span>
                            </label>
                          </div>
                        </div>
                      </li>
                      <li class="clearfix">
                        <div class="name">
                          <div class="checkbox-nice">
                            <input type="checkbox" id="todo-7" />
                            <label for="todo-7">
                              Printing new flyer <span class="label label-success">Low Priority</span>
                            </label>
                          </div>
                        </div>
                      </li>
                      <li class="clearfix">
                        <div class="name">
                          <div class="checkbox-nice">
                            <input type="checkbox" id="todo-8" />
                            <label for="todo-8">
                              Mila and Ryan wedding <span class="label label-danger">High Priority</span>
                            </label>
                          </div>
                        </div>
                      </li>
                      <li class="clearfix">
                        <div class="name">
                          <div class="checkbox-nice">
                            <input type="checkbox" id="todo-9" />
                            <label for="todo-9">
                              Checking the stock <span class="label label-success">Low Priority</span>
                            </label>
                          </div>
                        </div>
                      </li>
                    </ul>

                  </div>
                </div>
              </div>



            </div>

          </div>
        </div>

        <footer id="footer-bar" class="row">
          <p id="footer-copyright" class="col-xs-12">
            &copy; 2014 <a href="http://www.adbee.sk/" target="_blank">Adbee digital</a>. Powered by Centaurus Theme.
          </p>
        </footer>
      </div>
    </div>
  </div>
</div>

<div id="config-tool" class="closed">
  <a id="config-tool-cog">
    <i class="fa fa-cog"></i>
  </a>

  <div id="config-tool-options">
    <h4>Layout Options</h4>
    <ul>
      <li>
        <div class="checkbox-nice">
          <input type="checkbox" id="config-fixed-header" />
          <label for="config-fixed-header">
            Fixed Header
          </label>
        </div>
      </li>
      <li>
        <div class="checkbox-nice">
          <input type="checkbox" id="config-fixed-sidebar" />
          <label for="config-fixed-sidebar">
            Fixed Left Menu
          </label>
        </div>
      </li>
      <li>
        <div class="checkbox-nice">
          <input type="checkbox" id="config-fixed-footer" />
          <label for="config-fixed-footer">
            Fixed Footer
          </label>
        </div>
      </li>
      <li>
        <div class="checkbox-nice">
          <input type="checkbox" id="config-boxed-layout" />
          <label for="config-boxed-layout">
            Boxed Layout
          </label>
        </div>
      </li>
      <li>
        <div class="checkbox-nice">
          <input type="checkbox" id="config-rtl-layout" />
          <label for="config-rtl-layout">
            Right-to-Left
          </label>
        </div>
      </li>
    </ul>
    <br/>
    <h4>Skin Color</h4>
    <ul id="skin-colors" class="clearfix">
      <li>
        <a class="skin-changer" data-skin="" data-toggle="tooltip" title="Default" style="background-color: #34495e;">
        </a>
      </li>
      <li>
        <a class="skin-changer" data-skin="theme-white" data-toggle="tooltip" title="White/Green" style="background-color: #2ecc71;">
        </a>
      </li>
      <li>
        <a class="skin-changer blue-gradient" data-skin="theme-blue-gradient" data-toggle="tooltip" title="Gradient">
        </a>
      </li>
      <li>
        <a class="skin-changer" data-skin="theme-turquoise" data-toggle="tooltip" title="Green Sea" style="background-color: #1abc9c;">
        </a>
      </li>
      <li>
        <a class="skin-changer" data-skin="theme-amethyst" data-toggle="tooltip" title="Amethyst" style="background-color: #9b59b6;">
        </a>
      </li>
      <li>
        <a class="skin-changer" data-skin="theme-blue" data-toggle="tooltip" title="Blue" style="background-color: #2980b9;">
        </a>
      </li>
      <li>
        <a class="skin-changer" data-skin="theme-red" data-toggle="tooltip" title="Red" style="background-color: #e74c3c;">
        </a>
      </li>
      <li>
        <a class="skin-changer" data-skin="theme-whbl" data-toggle="tooltip" title="White/Blue" style="background-color: #3498db;">
        </a>
      </li>
    </ul>
  </div>
</div>
