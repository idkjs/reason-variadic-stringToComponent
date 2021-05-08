
[@react.component]
let make = (~visible=false) => {
  let myLabel =
    React.cloneElement(
      <span> {React.string("&times;")} </span>,
      {"aria-hidden": "true"},
    );
  let myButton =
    React.cloneElement(
      <button type_="button" className="close"> myLabel </button>,
      {"data-dismiss": "modal", "aria-label": "Close"},
    );
   !visible
    ? React.null
    :
  <DummyComponentThatMapsChildren>
    <div className="modal-dialog" role="document">
      <div className="modal-content">
        <div className="modal-header">
          <h5 className="modal-title"> {React.string("Modal title")} </h5>
          myButton
        </div>
        <div className="modal-body">
          <p> {React.string("Modal body text goes here.")} </p>
        </div>
        <div className="modal-footer">
          <button type_="button" className="btn btn-primary">
            {React.string("Save changes")}
          </button>
          {React.cloneElement(
             <button type_="button" className="btn btn-secondary">
               {React.string("Close")}
             </button>,
             {"data-dismiss": "modal"},
           )}
        </div>
      </div>
    </div>
  </DummyComponentThatMapsChildren>;
};
