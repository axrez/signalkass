const express = require('express');
const router = express.Router();

// @route:  api/device/post
// @disc:   Let the osciloscope update the database
// @access: Should be private but public for know
router.post("/post", (req, res) => {
  res.send("post");
})

module.exports = router;

