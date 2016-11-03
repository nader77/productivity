<div class="row">
  <div class="main-box clearfix project-box emerald-box col-sm-12">
    <div class="main-box-body clearfix">
      <p class="show-only-on-print"><?php print $date; ?></p>
      <div id="header" class="col-sm-12">
        <h1 id="project-title"><?php print t('Monthly Report'); ?><small><?php print ' - ' . $account . ' - ' . $project_title; ?></small></h1>
        <h2 id="gizra-logo">gizra</h2>
      </div>
      <div id="search-filter" class="row">
        <div class="col-sm-12 ">
          <div class="col-sm-4"><p><?php print t('Project:'); ?> </p></div>
          <div class="col-sm-4"><p><?php print t('Date:'); ?> </p></div>
        </div>
        <div class="col-sm-12">
          <div class="col-sm-4">
            <select id="project_filter" class="form-control">
              <?php foreach($projects as $nid => $project_name): ?>
                <option value="<?php print $nid;?>"<?php print ($nid == $current_project_id) ? 'selected' : ''; ?>><?php print $project_name; ?></option>
              <?php endforeach; ?>
            </select>
          </div>
          <div class="col-sm-4">
            <input type="text" id="month" name="month" class="monthPicker form-control" />
            <span class="add-on"><i class="icon-th"></i></span>
          </div>
          <div class="col-sm-4">
            <form>
            <div class="checkbox-nice">
              <input type="checkbox" id="estimation-based">
              <label for="estimation-based">
                Based on estimation of issue
              </label>
            </form>
            </div>
            <button class="btn btn-primary apply" type="button">Apply</button>
            <button class="btn btn-primary anytime" type="button">Any time</button>
            <button class="btn btn-primary year" type="button" data-toggle="popover" title="Can't be done" data-content="Please select a year first">All Year</button>
          </div>
        </div>
      </div>
      <div class="row">
        <div class="col-sm-12"><?php print $message; ?></div>
      </div>
     <?php print $table; ?>
    </div>
  </div>
</div>
