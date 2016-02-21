<div class="main-box clearfix project-box emerald-box">
  <div class="main-box-body clearfix">
    <div class="project-box-header emerald-bg">
      <div class="name">
        <?php print $link; ?>
      </div>
    </div>

    <div class="project-box-footer clearfix">
      <a href="#">
        <span class="value"><?php print $scope; ?>Hours</span>
        <span class="label">Project Scope</span>
      </a>
      <a href="#">
        <span class="value"><?php print $total_done; ?> Hours</span>
        <span class="label">Total Done</span>
      </a>
    </div>
    <div class="project-box-content">
      <span class="chart" data-percent="<?php print $percent_done; ?>">
          <span class="percent"></span>%<br/>
          <span class="lbl">completed</span>
      </span>
    </div>

    <div class="project-box-footer clearfix">
      <a href="#">
        <span class="value">TBD</span>
        <span class="label">Due Amount</span>
      </a>
      <a href="#">
        <span class="value">TBD</span>
        <span class="label">Paid amount</span>
      </a>
    </div>

    <div class="project-box-ultrafooter clearfix">
      <?php foreach($teams as $team): ?>
       <img class="project-img-owner" alt="" src="<?php print $team['pic']; ?>" data-toggle="tooltip" title="<?php print $team['name']; ?>"/>
      <?php endforeach; ?>

      <a href="<?php print $url; ?>" class="link pull-right">
        <i class="fa fa-arrow-circle-right fa-lg"></i>
      </a>
    </div>
  </div>
</div>

<!-- this page specific inline scripts -->
<script>
  jQuery(function() {
    jQuery  ('.chart').easyPieChart({
      easing: 'easeOutBounce',
      onStep: function(from, to, percent) {
        jQuery(this.el).find('.percent').text(Math.round(percent));
      },
      barColor: '#3498db',
      trackColor: '#f2f2f2',
      scaleColor: false,
      lineWidth: 8,
      size: 130,
      animate: 1500
    });
  });
</script>