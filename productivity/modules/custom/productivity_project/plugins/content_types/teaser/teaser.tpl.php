<div class="col-lg-4 col-md-6 col-sm-6">
  <div class="main-box clearfix project-box emerald-box">
    <div class="main-box-body clearfix">
      <div class="project-box-header emerald-bg">
        <div class="name">
          <a href="#">
            Nike site
          </a>
        </div>
      </div>

      <div class="project-box-footer clearfix">
        <a href="#">
          <span class="value">2000H</span>
          <span class="label">Project Scope</span>
        </a>
        <a href="#">
          <span class="value">18H</span>
          <span class="label">Last day H/Done</span>
        </a>
      </div>

      <div class="project-box-content">
        <span class="chart" data-percent="39">
            <span class="percent"></span>%<br/>
            <span class="lbl">completed</span>
        </span>
      </div>

      <div class="project-box-footer clearfix">
        <a href="#">
          <span class="value">$200</span>
          <span class="label">Due Amount</span>
        </a>
        <a href="#">
          <span class="value">$100000</span>
          <span class="label">Paid amount</span>
        </a>
      </div>

      <div class="project-box-ultrafooter clearfix">
        <img class="project-img-owner" alt="" src="<?php print $theme_path;?>/images/samples/scarlet-159.png" data-toggle="tooltip" title="Scarlett Johansson"/>
        <img class="project-img-owner" alt="" src="<?php print $theme_path;?>/images/samples/lima-300.jpg" data-toggle="tooltip" title="Adriana Lima"/>
        <img class="project-img-owner" alt="" src="<?php print $theme_path;?>/images/samples/emma-300.jpg" data-toggle="tooltip" title="Emma Watson"/>
        <img class="project-img-owner" alt="" src="<?php print $theme_path;?>/images/samples/angelina-300.jpg" data-toggle="tooltip" title="Angelina Jolie"/>

        <a href="#" class="link pull-right">
          <i class="fa fa-arrow-circle-right fa-lg"></i>
        </a>
      </div>
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