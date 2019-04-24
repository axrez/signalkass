import React from 'react';

import MeasureEntry from './MeasureEntry';

const DataTabel = ({ data }) => {
  console.log(data);
  if (typeof data === 'object') {
    const dates = data.map(e => e.created);
    console.log(dates);
  }
  return (
    <>
      <h4>table someday</h4>
      <ul>test</ul>
    </>
  );
};

export default DataTabel;
