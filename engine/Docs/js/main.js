(function(){
  const section = document.getElementById('sections')
  section.addEventListener('click', onSectionClick)
  const sections = document.getElementsByClassName('section')
  Array.from(sections).forEach((el) => {
  })

  function onSectionClick(e) {
    const target = e.target
    const link = target.classList.contains("code-toggle-collapse")
    if(!link) return

    const code = target.closest('.code')

    code.classList.toggle('code-opened')
  }
})()
