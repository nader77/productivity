<div class="row">
  <div class="main-box clearfix project-box emerald-box col-sm-12">
    <div class="main-box-body clearfix">
      <p class="show-only-on-print"><?php print date("F", mktime(null, null, null, $month, 1)) . " " . $year; ?></p>
      <div id="header" class="col-sm-12">
        <h1 id="project-title"><?php print t('Monthly Report'); ?><small><?php print ' - ' . $account . ' - ' . $project_title; ?></small></h1>
        <h2 id="gizra-logo">gizra</h2>
      </div>
      <div id="search-filter" class="row">
        <div class="col-sm-12 ">
          <div class="col-sm-5"><p><?php print t('Project:'); ?> </p></div>
          <div class="col-sm-3"><p><?php print t('Date:'); ?> </p></div>
        </div>
        <div class="col-sm-12">
          <div class="col-sm-5 ">
            <select id="project_filter" class="form-control">
              <?php foreach($projects as $nid => $project_name): ?>
                <option value="<?php print $nid;?>"<?php print ($nid == $current_project_id) ? 'selected' : ''; ?>><?php print $project_name; ?></option>
              <?php endforeach; ?>
            </select>
          </div>
          <div class="col-sm-3">
            <input id="date_filter" type="month" class="form-control" />
          </div>
          <input class="btn btn-primary col-sm-1" type="submit" value="Apply" />
        </div>
      </div>
      <div class="row">
        <div class="col-sm-12"><?php print $message; ?></div>
      </div>
     <?php print $table; ?>
    </div>
  </div>
</div>


