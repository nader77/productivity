<div class="row">
  <div class="main-box clearfix project-box emerald-box col-sm-12">
    <div class="main-box-body clearfix">
      <div id="search-filter" class="row">
        <div class="col-sm-12 ">
          <div class="col-sm-4"><p><?php print t('Employee:'); ?> </p></div>
          <div class="col-sm-4"><p><?php print t('Date:'); ?> </p></div>
        </div>
        <div class="col-sm-12">
          <div class="col-sm-4">
            <select id="uid" class="form-control">
              <?php foreach ($employees as $uid => $account): ?>
                <option value="<?php print $uid; ?>"<?php print ($uid == $current_uid) ? 'selected' : ''; ?>><?php print $account->name; ?></option>
              <?php endforeach; ?>
            </select>
          </div>
          <div class="col-sm-4">
              <input type="text" id="month" name="month" class="monthPicker form-control" />
              <span class="add-on"><i class="icon-th"></i></span>
          </div>
          <div class="col-sm-4">
            <button class="btn btn-primary apply" type="button">Apply</button>
            <?php if($pdf_url) : ?>
              <a href="<?php print $pdf_url; ?>" class="btn btn-primary" type="button">PDF</a>
            <?php endif; ?>
            <button class="btn btn-primary allpdf" type="button">Get all PDFs</button>
          </div>
        </div>
      </div>
      <div class="row">
        <div class="col-sm-12"><?php print $message; ?></div>
      </div>
    </div>
  </div>
</div>
<?php print $report ; ?>

