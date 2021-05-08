  [@react.component]
  let make = (~children, ()) => {
    <div
      className="modal modal-dialog-centered" id="exampleModal" role="dialog">
      {children->React.Children.mapWithIndex((element, index) => {
         React.cloneElement(
           element,
           {
             "key": {j|$index|j},
             "data-index": index,
             "tabIndex": "-1",
             "aria-hidden": "true",
           },
         )
       })}
    </div>;
  };
