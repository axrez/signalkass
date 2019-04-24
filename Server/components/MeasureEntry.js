import React from 'react';
import PropTypes from 'prop-types';

const MeasureEntry = ({ children }) => <li>{children}</li>;

MeasureEntry.propTypes = {
  children: PropTypes.node.isRequired,
};

export default MeasureEntry;
