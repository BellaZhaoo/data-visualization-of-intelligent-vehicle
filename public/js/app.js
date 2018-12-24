var jq=jQuery.noConflict();
jq(function() {
  jq(".navbar-expand-toggle").click(function() {
    jq(".app-container").toggleClass("expanded");
    return jq(".navbar-expand-toggle").toggleClass("fa-rotate-90");
  });
  return jq(".navbar-right-expand-toggle").click(function() {
    jq(".navbar-right").toggleClass("expanded");
    return jq(".navbar-right-expand-toggle").toggleClass("fa-rotate-90");
  });
});

jq(function() {
  return jq('select').select2();
});

jq(function() {
  return jq('.toggle-checkbox').bootstrapSwitch({
    size: "small"
  });
});

jq(function() {
  return jq('.match-height').matchHeight();
});

jq(function() {
  return jq('.datatable').DataTable({
    "dom": '<"top"fl<"clear">>rt<"bottom"ip<"clear">>'
  });
});

jq(function() {
  return jq(".side-menu .nav .dropdown").on('show.bs.collapse', function() {
    return jq(".side-menu .nav .dropdown .collapse").collapse('hide');
  });
});
